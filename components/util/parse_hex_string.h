#ifndef A50013BE_2667_4CBE_8FC9_6051BCD34B0F
#define A50013BE_2667_4CBE_8FC9_6051BCD34B0F

#include <array>
#include <cstdint>
#include <initializer_list>
#include <utility>

constexpr std::uint8_t parse_hex_digit(const char& c) noexcept {
  return c >= '0' && c <= '9'   ? c - '0'
         : c >= 'A' && c <= 'F' ? c - 'A' + 0xA
         : c >= 'a' && c <= 'f' ? c - 'a' + 0xA
                                : 0;
}

constexpr std::uint8_t parse_hex_tuple(const char& left,
                                       const char& right) noexcept {
  return parse_hex_digit(left) << 4 | parse_hex_digit(right);
}

template <std::size_t Length, std::size_t... Index>
constexpr auto parse_hex_string(const char (&input)[Length],
                                const std::index_sequence<Index...>&) {
  return std::array<uint8_t, (Length / 2)>{
      parse_hex_tuple(input[(Index * 2)], input[((Index * 2) + 1)])...};
}

template <std::size_t Length>
constexpr auto parse_hex_string(const char (&input)[Length]) {
  return parse_hex_string(input, std::make_index_sequence<(Length / 2)>{});
}

#endif /* A50013BE_2667_4CBE_8FC9_6051BCD34B0F */
