# ESP32 board with SHT40 temperature sensor

Takes measurements at long intervals, going do deep sleep meantime. At even longer intervals, a network connection is established to synchronize the time and to report collected measurements via MQTT.

## Configuration

Since server names, security keys etc. are sensible, it's up to you to add them to the configuration. Just copy [config.example.h](config.example.h) to [config.h](config.h) and adjust it to your needs.

## Building

This project is using ESP-IDF (comfortably from [Visual Studio Code](https://code.visualstudio.com), look for the [ESP-IDF extension](https://github.com/espressif/vscode-esp-idf-extension)), and needs a checkout of [esp-df-lib](https://github.com/UncleRus/esp-idf-lib) at the same level as this one, like

```
├── temperature_sensor
└── esp-idf-lib
```