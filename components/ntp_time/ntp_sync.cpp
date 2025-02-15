#include "ntp_sync.h"

#include <bounce.h>
#include <error.h>
#include <esp_log.h>
#include <experimental/scope>
#include <iostream>
#include <lwip/dns.h>
#include <lwip/udp.h>
#include <system_error>

using namespace std;
using namespace std::experimental;

ntp_sync::ntp_sync(const char *ntp_server_name) : ctrl{nullptr}
{
    ctrl = udp_new();
    if (ctrl == nullptr)
        throw runtime_error("UDP creation");

    lookup_ntp_host(ntp_server_name);
}

void ntp_sync::lookup_ntp_host(const char *host)
{
    ip_addr_t addr{};
    const auto dns_result = dns_gethostbyname(
        host, &addr,
        [](const char *name, const ip_addr_t *ipaddr, void *callback_arg) {
            (reinterpret_cast<ntp_sync *>(callback_arg))->dns_found(name, ipaddr);
        },
        this);

    switch (dns_result)
    {
    case ERR_OK:
        dns_found(host, &addr);
        return;

    case ERR_INPROGRESS:
        return;

    default:
        check(dns_result, "lookup NTP host");
        return;
    }
}

void ntp_sync::dns_found(const char *name, const ip_addr_t *ipaddr)
{
    if (ipaddr->type != IPADDR_TYPE_V4)
    {
        ESP_LOGW("ntp sync", "cannot resolve server host for IPv4");
        return;
    }

    cout << "NTP host resolved as " << hex << ntohl(ipaddr->u_addr.ip4.addr) << endl;
    cout.flush();

    check(udp_bind(ctrl, IP_ANY_TYPE, 0), "bind UDP port");
    check(udp_connect(ctrl, ipaddr, 7801), "set UDP destination");

    const string hello{"hello there"};

    auto txbuf = pbuf_alloc(PBUF_TRANSPORT, hello.size(), PBUF_RAM);
    if (txbuf == nullptr)
        throw runtime_error{"packet buffer allocation"};

    scope_exit free_rxbuf([txbuf] { pbuf_free(txbuf); });

    check(pbuf_take(txbuf, hello.data(), hello.size()), "copy data to txbuf");

    check(udp_send(ctrl, txbuf), "send UDP");
}

void ntp_sync::synchronized(timeval *tv)
{
    up.set_value();
}

future<void> ntp_sync::is_synchronized()
{
    return up.get_future();
}

ntp_sync::~ntp_sync()
{
    if (ctrl != nullptr)
        udp_remove(ctrl);
}
