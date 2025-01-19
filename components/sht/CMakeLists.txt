set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

idf_component_register(SRCS "compressed_measurement.cpp" "measurement.cpp" "sht.cpp"
    INCLUDE_DIRS "."
    REQUIRES sht4x
    PRIV_REQUIRES error)