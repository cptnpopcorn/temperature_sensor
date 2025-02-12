#include "nvs_access.h"

#include <error.h>

nvs_access::nvs_access(const char *namespace_name) : handle{}
{
    check(nvs_flash_init(), "NVS flash initialization");
    check(nvs_open(namespace_name, NVS_READWRITE, &handle));
}

nvs_access::~nvs_access()
{
    nvs_close(handle);
    check(nvs_flash_deinit(), "NVS flash deinitialization");
}
