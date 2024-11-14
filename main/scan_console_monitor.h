#ifndef AB3CCF24_1F28_4960_8A10_2E97287435E5
#define AB3CCF24_1F28_4960_8A10_2E97287435E5

#include <stddef.h>
#include <wifi_scan_monitor.h>

class scan_console_monitor final : public wifi_scan_monitor {
 public:
  virtual void add_result(const wifi_scan_result& result) override;

 private:
  size_t index = 0;
};

#endif /* AB3CCF24_1F28_4960_8A10_2E97287435E5 */
