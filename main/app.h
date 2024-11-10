#ifndef B3C11C8D_4E28_41F5_956E_A7ABD223F8B3
#define B3C11C8D_4E28_41F5_956E_A7ABD223F8B3

#include <sht.h>

class app final {
 public:
  app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl);
  app(const app&) = delete;
  app& operator=(const app&) = delete;
  void run();

 private:
  sht sensor;
};
#endif /* B3C11C8D_4E28_41F5_956E_A7ABD223F8B3 */
