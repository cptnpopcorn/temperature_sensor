#include "mqtt_config.h"

mqtt_config::mqtt_config(const std::string& broker_host,
                         const std::string& topic_root,
                         const std::span<const uint8_t>& ca_cert) noexcept
    : broker_host{broker_host}, topic_root{topic_root}, ca_cert{ca_cert} {}
