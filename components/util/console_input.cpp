#include "console_input.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

string console_read_line()
{
    for (vector<char> buffer;;)
    {
        const auto key = cin.get();
        switch (key)
        {
        case '\b':
            if (!buffer.empty())
                buffer.pop_back();
            cout << '\b' << ' ';
            break;
        case '\n':
        case '\r':
            return {buffer.cbegin(), buffer.cend()};
        default:
            if (key < ' ')
                continue;
            buffer.push_back(key);
            break;
        }

        cout << (char)key;
    }
}

tuple<bool, uint32_t> console_read_uint32()
{
    stringstream conv;
    conv << console_read_line();

    uint32_t value;
    conv >> value;

    return conv.fail() ? make_tuple(false, uint32_t{}) : make_tuple(true, value);
}
