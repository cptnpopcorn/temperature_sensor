#ifndef DBA56D7F_9EB5_4E8D_A051_BA5BE65F1F96
#define DBA56D7F_9EB5_4E8D_A051_BA5BE65F1F96

#include <vector>

#include "wifi_scan_result.h"

class wifi_scan_monitor {
 public:
  virtual void add_results(const std::vector<wifi_scan_result>& results) = 0;
};

#endif /* DBA56D7F_9EB5_4E8D_A051_BA5BE65F1F96 */
