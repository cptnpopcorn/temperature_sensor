#include "app.h"

#include <driver/usb_serial_jtag.h>
#include <driver/usb_serial_jtag_vfs.h>
#include <error.h>
#include <esp_task.h>
#include <interaction_loop.h>

#include <iostream>

#include "scan_console_visitor.h"
#include "setup_interaction.h"

using namespace std;

const char* const tag = "app";

app::app(i2c_port_t port, gpio_num_t sda, gpio_num_t scl)
    : evts{}, nvs{}, sensor{port, sda, scl}, station{evts, nvs} {}

void app::run() {
  prepare_console_input();
  setup();

  while (true) {
    cout << sensor.measure() << endl;
    cout.flush();
    vTaskDelay(4000 / portTICK_PERIOD_MS);
    scan_console_visitor scanmon;
    station.scan(scanmon);
    vTaskDelay(4000 / portTICK_PERIOD_MS);
  }
}

void app::prepare_console_input() {
  setvbuf(stdin, nullptr, _IONBF, 0);
  usb_serial_jtag_driver_config_t usb_serial_jtag_config{
      .tx_buffer_size = 1024, .rx_buffer_size = 1024};
  check(usb_serial_jtag_driver_install(&usb_serial_jtag_config),
        "JTAG driver install");
  usb_serial_jtag_vfs_use_driver();
}

void app::setup() {
  if (!usb_serial_jtag_is_connected()) return;

  setup_interaction setup{};
  interaction_loop loop{};
  loop.set(setup);
  loop.start();
}
