#ifndef BD052B90_1E07_4411_B1AE_2681FE387327
#define BD052B90_1E07_4411_B1AE_2681FE387327

#include <sht4x.h>

#include "measurement.h"

class sht final {
 public:
  sht(i2c_port_t port, gpio_num_t sda, gpio_num_t scl);
  const measurement measure();

 private:
  sht4x_t dev;
};

#endif /* BD052B90_1E07_4411_B1AE_2681FE387327 */
