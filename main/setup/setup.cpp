#include "setup.h"

#include <driver/uart.h>
#include <driver/uart_vfs.h>
#include <error.h>
#include <esp_sleep.h>
#include <esp_task.h>
#include <interaction_control.h>
#include <sdkconfig.h>

#include <chrono>
#include <iostream>
#include <string>

using namespace std;
using namespace chrono;

setup::setup(interaction &stop, wifi_station &station, const char *ntp_srv, measurement_traits::buffer_t &measurements,
             const sht_config &shtcfg, const mqtt_config &mqtt) noexcept
    : stop{stop}, wifi{*this, station}, time{*this, station, ntp_srv},
      measurements{*this, measurements, shtcfg, mqtt, station}
{
}

void setup::start(interaction_control &control)
{
    constexpr auto sleep_duration = 10s;
    cout << "sensor setup.." << endl;
    cout << "w - WiFi" << endl;
    cout << "t - time" << endl;
    cout << "m - measurements" << endl;
    cout << "s - sleep for " << sleep_duration << endl;
    cout << "q - quit" << endl;

    switch (cin.get())
    {
    case 'w':
        control.set(wifi);
        return;

    case 't':
        control.set(time);
        return;

    case 'm':
        control.set(measurements);
        return;

    case 's':
        check(esp_deep_sleep_try(microseconds{sleep_duration}.count()), "deep sleep with timer");
        return;

    case 'q':
        control.set(stop);
        return;
    }
}