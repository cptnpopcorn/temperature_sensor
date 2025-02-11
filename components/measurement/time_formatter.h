#ifndef A06B78EE_2C24_45BF_A5C1_18B020170403
#define A06B78EE_2C24_45BF_A5C1_18B020170403

#include <chrono>

template <class S, class T> void format_time(S &os, const T &time)
{
    const auto ds = std::chrono::floor<std::chrono::days>(time);
    const std::chrono::year_month_day ymd{ds};
    const std::chrono::hh_mm_ss daytime{std::chrono::floor<std::chrono::seconds>(time - ds)};
    os << ymd.year() << 'T' << daytime << 'Z';
}

#endif /* A06B78EE_2C24_45BF_A5C1_18B020170403 */
