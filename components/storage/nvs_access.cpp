#include "nvs_access.h"

#include <error.h>

using namespace std;

nvs_access::nvs_access(const char *namespace_name) : handle{}
{
    check(nvs_flash_init(), "NVS flash initialization");
    check(nvs_open(namespace_name, NVS_READWRITE, &handle));
}

std::string nvs_access::get_str(const char *key, const char *default_value)
{
    size_t length;
    const auto length_result = nvs_get_blob(handle, key, nullptr, &length);
    switch (length_result)
    {
    case ESP_OK: {
        string value(length, '\0');
        nvs_get_blob(handle, key, &value.at(0), &length);
        return value;
    }

    case ESP_ERR_NVS_NOT_FOUND:
        return {};

    default:
        check(length_result);
        return {};
    }
}

nvs_access::~nvs_access()
{
    nvs_close(handle);
    check(nvs_flash_deinit(), "NVS flash deinitialization");
}
