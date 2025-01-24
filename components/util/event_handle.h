#ifndef DD7CDC02_631D_4D3B_B194_F017D2C3C026
#define DD7CDC02_631D_4D3B_B194_F017D2C3C026

#include <esp_event.h>

#include "bounce.h"

class event_handle final {
 public:
  event_handle() noexcept = default;

  event_handle(esp_event_base_t base, int32_t id,
               esp_event_handler_instance_t instance) noexcept;

  event_handle(event_handle&&) noexcept;
  event_handle& operator=(event_handle&&) noexcept;
  ~event_handle();

 private:
  esp_event_base_t event_base{};
  int32_t event_id{};
  esp_event_handler_instance_t instance{};

  void swap(event_handle&) noexcept;
};

event_handle register_event(esp_event_base_t base, int32_t id, void* arg,
                            esp_event_handler_t handler);

#endif /* DD7CDC02_631D_4D3B_B194_F017D2C3C026 */
