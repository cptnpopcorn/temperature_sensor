#include <iostream>
#include <cstdint>

#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

void run();

extern "C"
{
    void app_main(void)
    {
        run();
    }
}

using namespace std;

void run()
{
    cout << "Temperature sensor app starting..." << endl;
}