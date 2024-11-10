#ifndef B1D83281_5CF6_403F_8ED5_AE2D05720D99
#define B1D83281_5CF6_403F_8ED5_AE2D05720D99

#include <esp_err.h>

#include <string>

void check(esp_err_t err);
void check(esp_err_t err, const std::string &what);
void error(const std::string &what);

#endif /* B1D83281_5CF6_403F_8ED5_AE2D05720D99 */
