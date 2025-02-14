#include "nvs_access.h"

#include <error.h>

using namespace std;

nvs_access::nvs_access(const char *namespace_name) : handle{}
{
    check(nvs_flash_init(), "NVS flash initialization");
    check(nvs_open(namespace_name, NVS_READWRITE, &handle));
}

uint32_t nvs_access::get_uint32(const char *key)
{
    uint32_t value;
    const auto result = nvs_get_u32(handle, key, &value);
    switch (result)
    {
    case ESP_OK:
        return value;

    case ESP_ERR_NVS_NOT_FOUND:
        return {};

    default:
        check(result);
        return {};
    }
}

void nvs_access::set_uint32(const char *key, const uint32_t &value)
{
    check(nvs_set_u32(handle, key, value));
}

std::string nvs_access::get_str(const char *key)
{
    size_t length{};
    const auto result = nvs_get_blob(handle, key, nullptr, &length);
    switch (result)
    {
    case ESP_OK: {
        string value(length, '\0');
        nvs_get_blob(handle, key, value.data(), &length);
        return value;
    }

    case ESP_ERR_NVS_NOT_FOUND:
        return {};

    default:
        check(result);
        return {};
    }
}

void nvs_access::set_str(const char *key, const std::string &value)
{
    check(nvs_set_blob(handle, key, value.data(), value.size()), "write NVS blob");
}

nvs_access::~nvs_access()
{
    nvs_close(handle);
    check(nvs_flash_deinit(), "NVS flash deinitialization");
}
