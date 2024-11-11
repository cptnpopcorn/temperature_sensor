#ifndef A7F279E4_92DF_4C61_82A9_B6BDA2F4C57A
#define A7F279E4_92DF_4C61_82A9_B6BDA2F4C57A

template <class T>
class guard final {
 public:
  guard(T& func) : func{func} {}
  guard(guard&&) = default;
  guard& operator=(guard&&) = default;
  ~guard() { func(); }

 private:
  T& func;
};

template <class T>
auto make_guard(T& func) {
  return guard<T>(func);
}

#endif /* A7F279E4_92DF_4C61_82A9_B6BDA2F4C57A */
