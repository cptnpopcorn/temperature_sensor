#include "wifi_config.h"

#include <utility>

using namespace std;

wifi_config::wifi_config(const string& ssid, const string& passwd)
    : ssid{ssid}, passwd{passwd} {}

wifi_config::wifi_config(const string&& ssid, const string&& passwd) noexcept
    : ssid{move(ssid)}, passwd{move(passwd)} {}
