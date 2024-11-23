#include "scan_console_visitor.h"

#include <iostream>

using namespace std;

bool scan_console_visitor::continue_with_result(
    const wifi_scan_result& result) {
  cout << "[" << index++ << "] " << result.ssid << endl;
  return true;
}
