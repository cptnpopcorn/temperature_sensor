#ifndef E9F1A826_B0E3_4084_8780_A580675EAAA9
#define E9F1A826_B0E3_4084_8780_A580675EAAA9

#include <cstdint>
#include <span>
#include <string>

class mqtt_config final
{
  public:
    using cert_t = std::span<const uint8_t>;

    mqtt_config(const std::string &broker_host, const std::string &topic_root, const cert_t &ca_cert,
                const cert_t &client_cert, const cert_t &client_key) noexcept;

    const std::string broker_host;
    const std::string topic_root;
    const cert_t ca_cert;

    // those are either both present or both not present, to use client auth
    const cert_t client_cert;
    const cert_t client_key;
};

#endif /* E9F1A826_B0E3_4084_8780_A580675EAAA9 */
