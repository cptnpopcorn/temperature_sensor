#include "console_input.h"

#include <iostream>
#include <vector>

using namespace std;

string console_read_line() {
  for (vector<char> buffer;;) {
    const auto key = cin.get();
    switch (key) {
      case '\b':
        if (!buffer.empty()) buffer.pop_back();
        cout << '\b' << ' ';
        break;
      case '\n':
      case '\r':
        return {buffer.cbegin(), buffer.cend()};
      default:
        if (key < ' ') continue;
        buffer.push_back(key);
        break;
    }

    cout << (char)key;
  }
}
