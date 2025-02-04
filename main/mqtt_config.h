#ifndef E9F1A826_B0E3_4084_8780_A580675EAAA9
#define E9F1A826_B0E3_4084_8780_A580675EAAA9

#include <cstdint>
#include <span>
#include <string>

class mqtt_config final {
 public:
  mqtt_config(const std::string& broker_host, const std::string& topic_root,
              const std::span<const uint8_t>& ca_cert) noexcept;

  const std::string broker_host;
  const std::string topic_root;
  const std::span<const uint8_t> ca_cert;
};

#endif /* E9F1A826_B0E3_4084_8780_A580675EAAA9 */
