idf_component_register(SRCS "sht_config.cpp" "compressed_measurement.cpp" "measurement.cpp" "sht.cpp"
    INCLUDE_DIRS "."
    REQUIRES sht4x
    PRIV_REQUIRES error)