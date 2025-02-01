# ESP32 board with SHT40 temperature sensor

Takes measurements at long intervals, going do deep sleep meantime. At even longer intervals, a network connection is established to synchronize the time and to report collected measurements via MQTT.

## Configuration

All build-time settings are available through the ESP-IDF under the "Temperature Sensor" menu. (use [_menuconfig_](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/kconfig/project-configuration-guide.html#editing-the-configuration))

## Building

This project is using ESP-IDF (comfortably from [Visual Studio Code](https://code.visualstudio.com), look for the [ESP-IDF extension](https://github.com/espressif/vscode-esp-idf-extension)), and needs a checkout of [esp-df-lib](https://github.com/UncleRus/esp-idf-lib) at the same level as this one, like

```
├── temperature_sensor
└── esp-idf-lib
```