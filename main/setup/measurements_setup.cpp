#include "measurements_setup.h"

#include <console_input.h>
#include <interaction_control.h>
#include <nvs_access.h>
#include <publisher.h>
#include <sht.h>
#include <time_formatter.h>
#include <wifi_connection.h>

#include <chrono>
#include <iostream>
#include <string>

#include "../app_storage.h"
#include "../mqtt_config.h"

using namespace std;
using namespace std::chrono;

measurements_setup::measurements_setup(interaction &setup, buffer_t &measurements, const sht_config &shtcfg,
                                       nvs_access &nvs, const mqtt_config &mqtt, wifi_station &wifi) noexcept
    : setup{setup}, measurements{measurements}, shtcfg{shtcfg}, nvs{nvs}, mqtt{mqtt}, sta{wifi}
{
}

const string undefined{"!undefined!"};

const string &empty_as_undefined(const string &value)
{
    return value.length() == 0 ? undefined : value;
}

void measurements_setup::start(interaction_control &control)
{
    const auto topic = nvs.get_str(app_storage::mqtt_topic_key);
    const hh_mm_ss<seconds> measurement_interval{
        static_cast<seconds>(nvs.get_uint32(app_storage::measurement_interval_key))};

    const hh_mm_ss<seconds> synchronization_interval{
        static_cast<seconds>(nvs.get_uint32(app_storage::synchronization_interval_key))};

    cout << "Measurements setup (" << measurements.size() << " measurements present) for topic '"
         << empty_as_undefined(topic) << "', sampled every " << measurement_interval << ", published every "
         << synchronization_interval << ".." << endl;

    cout << "l - list measurements" << endl;
    cout << "a - add measurement now" << endl;
    cout << "t - set mqtt topic" << endl;
    cout << "m - show mqtt config" << endl;
    cout << "p - publish measurements" << endl;
    cout << "i - set measurement interval" << endl;
    cout << "s - set synchronization interval" << endl;
    cout << "q - quit" << endl;

    switch (cin.get())
    {
    case 'l':
        for (const auto &m : measurements)
        {
            format_time(cout, m.time());
            cout << ' ' << m.temperature() << " deg " << m.humidity() << " %" << endl;
        }
        return;

    case 'a': {
        sht sensor{shtcfg};
        const auto m = sensor.measure();
        cout << "measured " << m << endl;
        measurements.write({system_clock::now(), m.temperature, m.humidity});
        return;
    }

    case 't': {
        cout << "enter new topic: ";
        const auto new_topic = console_read_line();
        cout << endl;
        if (new_topic.length() == 0)
        {
            cout << "empty input -> no change" << endl;
            return;
        }
        if (new_topic == topic)
        {
            cout << "topic identical -> no change" << endl;
            return;
        }
        nvs.set_str(app_storage::mqtt_topic_key, new_topic);
        return;
    }

    case 'm':
        cout << "broker URI: " << mqtt.broker_host << endl;
        cout << "topic root: " << mqtt.topic_root << endl;
        return;

    case 'p':
        publish_measurements();
        return;

    case 'i': {
        cout << "enter new measurement interval in seconds: ";
        const auto [valid, seconds] = console_read_uint32();
        cout << endl;
        if (!valid)
        {
            cout << "not a valid number of seconds" << endl;
            return;
        }
        if (seconds == nvs.get_uint32(app_storage::measurement_interval_key))
        {
            cout << "interval identical - no change" << endl;
            return;
        }
        nvs.set_uint32(app_storage::measurement_interval_key, seconds);
        return;
    }

    case 's': {
        cout << "enter new synchronization interval in seconds: ";
        const auto [valid, seconds] = console_read_uint32();
        cout << endl;
        if (!valid)
        {
            cout << "not a valid number of seconds" << endl;
            return;
        }
        if (seconds == nvs.get_uint32(app_storage::synchronization_interval_key))
        {
            cout << "interval identical - no change" << endl;
            return;
        }
        nvs.set_uint32(app_storage::synchronization_interval_key, seconds);
        return;
    }

    case 'q':
        control.set(setup);
        return;
    }
}

void measurements_setup::publish_measurements()
{
    cout << "connecting WiFi";
    wifi_connection connection{sta};

    auto is_wifi_up = connection.is_up();
    for ([[maybe_unused]] auto i = 10; i != 0; --i)
    {
        if (is_wifi_up.wait_for(1s) == future_status::ready)
        {
            cout << endl << "WiFi connected" << endl;
            const auto topic = "setup/" + mqtt.topic_root + '/' + nvs.get_str(app_storage::mqtt_topic_key);
            cout << "connecting to MQTT broker " << mqtt.broker_host << " for topic " << topic;

            publisher pub{mqtt.broker_host, topic, mqtt.ca_cert, mqtt.client_cert, mqtt.client_key};

            auto is_mqtt_connected = pub.is_connected();
            for ([[maybe_unused]] auto j = 10; j != 0; --j)
            {
                if (is_mqtt_connected.wait_for(1s) == future_status::ready)
                {
                    cout << endl << "MQTT connected" << endl;
                    cout << "Publishing stored measurements" << endl;
                    for (const auto &m : measurements)
                    {
                        if (!pub.publish(m))
                        {
                            cout << "error while publishing" << endl;
                            return;
                        }
                    }
                    return;
                }
                cout << '.';
                cout.flush();
            }
            cout << endl << "MQTT connection timeout reached" << endl;
            return;
        }
        cout << '.';
        cout.flush();
    }
    cout << endl << "WiFi connection timeout reached" << endl;
}
