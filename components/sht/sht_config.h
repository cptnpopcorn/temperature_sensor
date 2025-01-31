#ifndef F08D374A_3253_4D20_93A5_A198FEF6C8EC
#define F08D374A_3253_4D20_93A5_A198FEF6C8EC

#include <sht4x.h>

class sht_config final {
 public:
  sht_config(i2c_port_t port, gpio_num_t sda, gpio_num_t scl) noexcept;

  i2c_port_t get_port() const noexcept;
  gpio_num_t get_sda() const noexcept;
  gpio_num_t get_scl() const noexcept;

 private:
  const i2c_port_t port;
  const gpio_num_t sda;
  const gpio_num_t scl;
};

#endif /* F08D374A_3253_4D20_93A5_A198FEF6C8EC */
