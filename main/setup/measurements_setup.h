#ifndef F7D4BD4A_C0D5_4C88_8C82_EE087512AB85
#define F7D4BD4A_C0D5_4C88_8C82_EE087512AB85

#include <interaction.h>
#include <measurement_traits.h>

class mqtt_config;
class sht_config;
class wifi_station;

class measurements_setup : public interaction
{
  public:
    using buffer_t = measurement_traits::buffer_t;

    measurements_setup(interaction &setup, buffer_t &measurements, const sht_config &shtcfg, const mqtt_config &mqtt,
                       wifi_station &station) noexcept;

    void start(interaction_control &) override;

  private:
    void publish_measurements();
    interaction &setup;
    buffer_t &measurements;
    const sht_config &shtcfg;
    const mqtt_config &mqtt;
    wifi_station &sta;
};

#endif /* F7D4BD4A_C0D5_4C88_8C82_EE087512AB85 */
