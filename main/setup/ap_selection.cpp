#include "ap_selection.h"

#include <iostream>

using namespace std;

constexpr auto min_select_key = '0';
constexpr auto max_select_key = '9';
constexpr auto max_num_choices = max_select_key - min_select_key;

bool ap_selection::continue_with_result(const wifi_scan_result& result) {
  ssids.push_back(result.ssid);
  if (ssids.size() < max_num_choices) return true;

  user_select(true);
  ssids.clear();

  return !stop;
}

void ap_selection::flush() {
  if (!stop) user_select(false);
  ssids.clear();
}

const std::string& ap_selection::get_selected_ssid() const noexcept {
  return selected_ssid;
}

void ap_selection::user_select(bool expect_more) {
  if (ssids.empty()) return;

  for (;;) {
    for (auto i = 0; i < ssids.size(); ++i) {
      cout << '[' << i << ']' << ' ' << ssids[i] << endl;
    }

    if (ssids.size() > 1) cout << min_select_key << '-';
    cout << static_cast<char>(min_select_key + ssids.size() - 1)
         << " - select access point" << endl;

    cout << (expect_more ? "m - scan for more" : "(end of results)") << endl;
    cout << "q - quit" << endl;

    const auto key = cin.get();

    if (key >= min_select_key) {
      const auto select_index = key - min_select_key;

      if (select_index < ssids.size()) {
        selected_ssid = ssids[select_index];
        cout << "selected " << selected_ssid << endl;
        stop = true;
        return;
      }
    }

    switch (key) {
      case 'm':
        if (expect_more) return;
        continue;

      case 'q':
        stop = true;
        return;
    }
  }
}
