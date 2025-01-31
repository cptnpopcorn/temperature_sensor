#ifndef BD052B90_1E07_4411_B1AE_2681FE387327
#define BD052B90_1E07_4411_B1AE_2681FE387327

#include <sht4x.h>

#include "measurement.h"

class sht_config;

class sht final {
 public:
  sht(const sht_config&);
  measurement measure();
  ~sht();

 private:
  sht4x_t dev;
};

#endif /* BD052B90_1E07_4411_B1AE_2681FE387327 */
