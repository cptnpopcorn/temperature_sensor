idf_component_register(SRCS "mqtt_event_handle.cpp" "publisher.cpp"
    INCLUDE_DIRS "."
    REQUIRES sht storage mqtt wifi
    PRIV_REQUIRES error)
