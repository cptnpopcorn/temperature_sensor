#include "sht_config.h"

sht_config::sht_config(i2c_port_t port, gpio_num_t sda, gpio_num_t scl) noexcept
    : port{port}, sda{sda}, scl{scl} {}

i2c_port_t sht_config::get_port() const noexcept { return port; }
gpio_num_t sht_config::get_sda() const noexcept { return sda; }
gpio_num_t sht_config::get_scl() const noexcept { return scl; }
