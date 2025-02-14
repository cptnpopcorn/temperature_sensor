#ifndef BFB57D3A_6315_4528_A10C_9AEC1F61A48A
#define BFB57D3A_6315_4528_A10C_9AEC1F61A48A

#include <cstdint>
#include <nvs_flash.h>
#include <string>

class nvs_access final
{
  public:
    nvs_access(const char *namespace_name);
    nvs_access(const nvs_access &) = delete;
    nvs_access &operator=(const nvs_access &) = delete;

    uint32_t get_uint32(const char *key);
    void set_uint32(const char *key, const uint32_t &value);

    std::string get_str(const char *key);
    void set_str(const char *key, const std::string &value);

    ~nvs_access();

  private:
    nvs_handle_t handle;
};

#endif /* BFB57D3A_6315_4528_A10C_9AEC1F61A48A */
