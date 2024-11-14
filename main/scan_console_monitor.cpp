#include "scan_console_monitor.h"

#include <iostream>

using namespace std;

void scan_console_monitor::add_result(const wifi_scan_result& result) {
  cout << "[" << index++ << "] " << result.ssid << endl;
}
