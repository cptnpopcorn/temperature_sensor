#include "sht.h"

#include <error.h>

#include "sht_config.h"

sht::sht(const sht_config &config) : dev{} {
  check(i2cdev_init(), "SHT lib initialization");
  check(sht4x_init_desc(&dev, config.get_port(), config.get_sda(),
                        config.get_scl()),
        "SHT descriptor init");
  check(sht4x_init(&dev), "SHT device init");
}

measurement sht::measure() {
  measurement m{};
  check(sht4x_measure(&dev, &m.temperature, &m.humidity), "SHT measurement");
  return m;
}

sht::~sht() {
  check(sht4x_free_desc(&dev));
  check(i2cdev_done());
}
