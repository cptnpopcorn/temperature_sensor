#ifndef DBA56D7F_9EB5_4E8D_A051_BA5BE65F1F96
#define DBA56D7F_9EB5_4E8D_A051_BA5BE65F1F96

#include <vector>

#include "wifi_scan_result.h"

class wifi_scan_visitor {
 public:
  virtual bool continue_with_result(const wifi_scan_result& result) = 0;
};

#endif /* DBA56D7F_9EB5_4E8D_A051_BA5BE65F1F96 */
