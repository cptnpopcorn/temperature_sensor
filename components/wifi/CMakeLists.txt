idf_component_register(SRCS "wifi_config.cpp" "wifi_scan_result.cpp" "wifi_station.cpp"
    INCLUDE_DIRS "."
    PRIV_REQUIRES esp_wifi storage error util)