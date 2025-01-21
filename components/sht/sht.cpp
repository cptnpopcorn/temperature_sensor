#include "sht.h"

#include <error.h>

sht::sht(i2c_port_t port, gpio_num_t sda, gpio_num_t scl) : dev{} {
  check(i2cdev_init(), "SHT lib initialization");
  check(sht4x_init_desc(&dev, port, sda, scl), "SHT descriptor init");
  check(sht4x_init(&dev), "SHT device init");
}

measurement sht::measure() {
  measurement m{};
  check(sht4x_measure(&dev, &m.temperature, &m.humidity), "SHT measurement");
  return m;
}