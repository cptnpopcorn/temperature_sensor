idf_component_register(SRCS "ntp_sync.cpp"
    INCLUDE_DIRS "."
    PRIV_REQUIRES error esp_netif lwip util)