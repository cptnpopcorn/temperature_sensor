#include "app.h"

#include <driver/usb_serial_jtag.h>
#include <driver/usb_serial_jtag_vfs.h>
#include <error.h>
#include <esp_sleep.h>
#include <esp_task.h>
#include <interaction_loop.h>
#include <sht.h>

#include <iostream>

#include "scan_console_visitor.h"
#include "setup/setup.h"

using namespace std;

const char *const tag = "app";

app::app(const sht_config &shtcfg, const char *ntp_server_name, buffer_t &measurements,
         int default_measurement_interval_seconds, int default_synchronization_interval_seconds,
         const ::mqtt_config &mqtt) noexcept
    : evts{}, nvs{"tempsens"}, shtcfg{shtcfg}, station{evts, nvs}, ntp_srv{ntp_server_name}, measurements{measurements},
      mqtt{mqtt}
{
}

void app::run()
{
    if (usb_serial_jtag_is_connected())
    {
        setup();
    }

    sht sensor{shtcfg};
    while (true)
    {
        cout << sensor.measure() << endl;
        cout.flush();
        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}

void app::setup()
{
    prepare_console_input();
    interaction_loop loop{};
    ::setup setup{loop.stop(), station, ntp_srv, measurements, shtcfg, mqtt};
    loop.set(setup);
    loop.start();
}

void app::prepare_console_input()
{
    setvbuf(stdin, nullptr, _IONBF, 0);
    usb_serial_jtag_driver_config_t usb_serial_jtag_config{.tx_buffer_size = 1024, .rx_buffer_size = 1024};
    check(usb_serial_jtag_driver_install(&usb_serial_jtag_config), "JTAG driver install");
    usb_serial_jtag_vfs_use_driver();
}