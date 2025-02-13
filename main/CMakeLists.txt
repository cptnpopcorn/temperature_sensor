set(COMPONENT_SRCS "mqtt_config.cpp" "scan_console_visitor.cpp" "app_main.cpp" "app.cpp" "app_storage.cpp"
    "setup/setup.cpp" "setup/wifi_setup.cpp" "setup/ap_selection.cpp" "setup/time_setup.cpp" "setup/measurements_setup.cpp")

set(COMPONENT_ADD_INCLUDEDIRS ".")

if (CONFIG_MQTT_USE_TLS)
    list(APPEND COMPONENT_EMBED_TXTFILES "security/ca.crt")
endif()

if (CONFIG_MQTT_TLS_CLIENT_AUTH)
    list(APPEND COMPONENT_EMBED_TXTFILES "security/client.crt" "security/client.key")
endif()

register_component()
