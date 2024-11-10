idf_component_register(SRCS "measurement.cpp" "sht.cpp"
    INCLUDE_DIRS "."
    REQUIRES sht4x
    PRIV_REQUIRES error)