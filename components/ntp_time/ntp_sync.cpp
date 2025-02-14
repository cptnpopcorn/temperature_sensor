#include "ntp_sync.h"

#include <bounce.h>
#include <error.h>
#include <iostream>
#include <lwip/dns.h>

using namespace std;

ntp_sync::ntp_sync(const char *ntp_server_name)
{
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
    cout << "NTP host resolved as " << hex << lwip_ntohl(ipaddr->u_addr.ip4.addr) << endl;
    cout.flush();
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
}
