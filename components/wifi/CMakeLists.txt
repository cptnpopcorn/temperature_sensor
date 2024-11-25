idf_component_register(SRCS "wifi_connection.cpp" "wifi_config.cpp" "wifi_scan_result.cpp" "wifi_station.cpp"
    INCLUDE_DIRS "."
    PRIV_REQUIRES error util storage esp_wifi)