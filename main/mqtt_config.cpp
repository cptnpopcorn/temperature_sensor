#include "mqtt_config.h"

mqtt_config::mqtt_config(const std::string& broker_host,
                         const std::string& topic_root) noexcept
    : broker_host{broker_host}, topic_root{topic_root} {}
