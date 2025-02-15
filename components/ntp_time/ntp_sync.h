#ifndef B8807F32_534D_46EE_81AD_65EF7EACB1D0
#define B8807F32_534D_46EE_81AD_65EF7EACB1D0

#include <cstddef>
#include <future>
#include <lwip/ip_addr.h>

struct timeval;
struct udp_pcb;

class ntp_sync final
{
  public:
    ntp_sync(const char *ntp_server_name);
    ntp_sync(const ntp_sync &) = delete;
    ntp_sync &operator=(const ntp_sync &) = delete;
    std::future<void> is_synchronized();
    ~ntp_sync();

  private:
    void lookup_ntp_host(const char *host);
    void dns_found(const char *name, const ip_addr_t *ipaddr);
    void synchronized(timeval *tv);

    udp_pcb *ctrl;
    std::promise<void> up;
};

#endif /* B8807F32_534D_46EE_81AD_65EF7EACB1D0 */
