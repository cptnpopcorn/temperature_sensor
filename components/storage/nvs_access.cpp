#include "nvs_access.h"

#include <error.h>
#include <nvs_flash.h>

nvs_access::nvs_access()
{
    check(nvs_flash_init(), "NVS flash initialization");
}
