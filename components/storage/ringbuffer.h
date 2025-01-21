#ifndef E56756F2_FCE9_4506_8291_7FDAF2C00E14
#define E56756F2_FCE9_4506_8291_7FDAF2C00E14

#include <algorithm>
#include <array>

template <class Item, std::size_t Size>
class ringbuffer_iterator final {
 private:
  using iterator_t = std::array<Item, Size>::const_iterator;

 public:
  ringbuffer_iterator(const std::array<Item, Size>& items, size_t pos) noexcept
      : pos{items.cbegin() + pos}, start{items.cbegin()}, end{items.cend()} {}

  ringbuffer_iterator& operator++() noexcept {
    auto next_pos = ++pos;
    pos = next_pos == end ? start : next_pos;
    return *this;
  }

  bool operator!=(const ringbuffer_iterator<Item, Size>& other) const noexcept {
    return pos != other.pos;
  }

  const Item& operator*() { return *pos; }

 private:
  iterator_t pos;
  const iterator_t start;
  const iterator_t end;
};

template <class Item, std::size_t Size>
class ringbuffer final {
 public:
  using size_t = std::size_t;
  using const_iterator = ringbuffer_iterator<Item, Size>;

  size_t size() const noexcept { return write_size; }

  void write(const Item& item) noexcept {
    storage[write_position] = item;
    write_position = (write_position + 1) % storage.size();
    write_size = std::min(write_size + 1, storage.size());
  }

  const_iterator begin() const noexcept {
    return {storage,
            (storage.size() + write_position - write_size) % storage.size()};
  }

  const_iterator end() const noexcept { return {storage, write_position}; }

  void flush(size_t size) noexcept { write_size -= size; }

 private:
  size_t write_size;
  size_t write_position;
  std::array<Item, Size> storage;
};

#endif /* E56756F2_FCE9_4506_8291_7FDAF2C00E14 */
