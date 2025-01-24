#include "mqtt_config.h"

mqtt_config::mqtt_config(const std::string& server_uri,
                         const std::string& topic_root) noexcept
    : server_uri{server_uri}, topic_root{topic_root} {}
