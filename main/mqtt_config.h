#ifndef E9F1A826_B0E3_4084_8780_A580675EAAA9
#define E9F1A826_B0E3_4084_8780_A580675EAAA9

#include <string>

class mqtt_config final {
 public:
  mqtt_config(const std::string& server_uri,
              const std::string& topic_root) noexcept;

  const std::string server_uri;
  const std::string topic_root;
};

#endif /* E9F1A826_B0E3_4084_8780_A580675EAAA9 */
