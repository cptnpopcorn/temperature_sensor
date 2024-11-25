#ifndef B87CF526_8F6F_4C1F_9C85_5AE4BD212C4E
#define B87CF526_8F6F_4C1F_9C85_5AE4BD212C4E

#include <utility>

template <class T, class Method, Method m, class... Params>
static auto bounce(void *priv, Params... params)
    -> decltype(((*reinterpret_cast<T *>(priv)).*m)(params...)) {
  return ((*reinterpret_cast<T *>(priv)).*m)(std::forward<Params>(params)...);
}

#define BOUNCE(c, m) bounce<c, decltype(&c::m), &c::m>

#endif /* B87CF526_8F6F_4C1F_9C85_5AE4BD212C4E */
