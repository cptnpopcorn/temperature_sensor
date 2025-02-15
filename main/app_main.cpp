#include <esp_log.h>
#include <sdkconfig.h>

#include <cstddef>
#include <cstring>
#include <iostream>
#include <lwip/udp.h>
#include <nvs_access.h>
#include <stdexcept>

#include "app.h"
#include "app_storage.h"
#include "mqtt_config.h"

using namespace std;

const char *const tag = "app";

// cold boot assures zero-init, deep sleep will preserve content in RTC RAM
RTC_DATA_ATTR uint8_t measurements[sizeof(app::buffer_t)];

#ifdef CONFIG_MQTT_USE_TLS
extern "C"
{
    extern const uint8_t _binary_ca_crt_start[] asm("_binary_ca_crt_start");
    extern const uint8_t _binary_ca_crt_end[] asm("_binary_ca_crt_end");
}
span<const uint8_t> get_ca_crt()
{
    return {&_binary_ca_crt_start[0], &_binary_ca_crt_end[0]};
}
#else
span<const uint8_t> get_ca_crt()
{
    return {};
}
#endif

#ifdef CONFIG_MQTT_TLS_CLIENT_AUTH
extern "C"
{
    extern const uint8_t _binary_client_crt_start[] asm("_binary_client_crt_start");
    extern const uint8_t _binary_client_crt_end[] asm("_binary_client_crt_end");
    extern const uint8_t _binary_client_key_start[] asm("_binary_client_key_start");
    extern const uint8_t _binary_client_key_end[] asm("_binary_client_key_end");
    span<const uint8_t> get_client_crt()
    {
        return {&_binary_client_crt_start[0], &_binary_client_crt_end[0]};
    }
    span<const uint8_t> get_client_key()
    {
        return {&_binary_client_key_start[0], &_binary_client_key_end[0]};
    }
}
#else
span<const uint8_t> get_client_crt()
{
    return {};
}
span<const uint8_t> get_client_key()
{
    return {};
}
#endif

extern "C"
{
    void app_main(void)
    {
        ESP_LOGI(tag, "temperature sensor app starting...");

        try
        {
            nvs_access nvs{"tempsens"};

            if (nvs.get_uint32(app_storage::measurement_interval_key) == 0u)
            {
                nvs.set_uint32(app_storage::measurement_interval_key, CONFIG_MEASUREMENT_INTERVAL_SECONDS);
            }

            if (nvs.get_uint32(app_storage::synchronization_interval_key) == 0u)
            {
                nvs.set_uint32(app_storage::synchronization_interval_key, CONFIG_SYNCHRONIZATION_INTERVAL_SECONDS);
            }

            pbuf_init();
            udp_init();

            app{{I2C_NUM_0, static_cast<gpio_num_t>(CONFIG_SDA_PIN), static_cast<gpio_num_t>(CONFIG_SCL_PIN)},
                CONFIG_NTP_SRV,
                *reinterpret_cast<app::buffer_t *>(measurements),
                nvs,
                mqtt_config{CONFIG_MQTT_BROKER_HOSTNAME, CONFIG_MQTT_TOPIC_ROOT, get_ca_crt(), get_client_crt(),
                            get_client_key()}}
                .run();
        }
        catch (const exception &e)
        {
            ESP_LOGE(tag, "%s", e.what());
        }
    }
}
