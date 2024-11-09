#include <iostream>
#include <cstdint>
#include <system_error>

#include <sdkconfig.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_system.h>
#include <sht4x.h>

void run();

extern "C"
{
    void app_main(void)
    {
        run();
    }
}

using namespace std;

const char *tag = "app";

void run()
{
    ESP_LOGI(tag, "temperature sensor app starting...");

    ESP_ERROR_CHECK(i2cdev_init());
    sht4x_t dev{};
    ESP_ERROR_CHECK(sht4x_init_desc(&dev, I2C_NUM_0, GPIO_NUM_19, GPIO_NUM_20));
    ESP_ERROR_CHECK(sht4x_init(&dev));

    float temperature;
    float humidity;
    ESP_ERROR_CHECK(sht4x_measure(&dev, &temperature, &humidity));

    cout << temperature << " °C " << humidity << " %" << endl;
}