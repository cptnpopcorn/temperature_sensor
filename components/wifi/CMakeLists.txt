idf_component_register(SRCS "wifi_connection.cpp" "wifi_config.cpp" "wifi_scan_result.cpp" "wifi_station.cpp"
    INCLUDE_DIRS "."
    REQUIRES util
    PRIV_REQUIRES error storage esp_wifi)