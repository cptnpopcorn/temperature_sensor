#ifndef E56756F2_FCE9_4506_8291_7FDAF2C00E14
#define E56756F2_FCE9_4506_8291_7FDAF2C00E14

#include <algorithm>
#include <array>

template <class Item, std::size_t Size>
class ringbuffer_iterator final {
 private:
  using array_t = std::array<Item, Size>;

 public:
  ringbuffer_iterator(const std::array<Item, Size>& items, size_t pos) noexcept
      : items{items}, pos{pos} {}

  ringbuffer_iterator& operator++() noexcept {
    ++pos;
    return *this;
  }

  bool operator!=(const ringbuffer_iterator<Item, Size>& other) const noexcept {
    return pos != other.pos;
  }

  const Item& operator*() { return items[pos % items.size()]; }

 private:
  const array_t& items;
  size_t pos;
};

template <class Item, std::size_t Size>
class ringbuffer final {
 public:
  using size_t = std::size_t;
  using const_iterator = ringbuffer_iterator<Item, Size>;

  size_t size() const noexcept { return write_size; }

  void write(const Item& item) noexcept {
    items[write_position] = item;
    write_position = (write_position + 1) % items.size();
    write_size = std::min(write_size + 1, items.size());
  }

  const_iterator begin() const noexcept {
    return {items, (items.size() + write_position - write_size) % items.size()};
  }

  const_iterator end() const noexcept {
    return {items, write_position >= write_size
                       ? write_position
                       : write_position + items.size()};
  }

  void flush(size_t size) noexcept { write_size -= size; }

 private:
  size_t write_size;
  size_t write_position;
  std::array<Item, Size> items;
};

#endif /* E56756F2_FCE9_4506_8291_7FDAF2C00E14 */
