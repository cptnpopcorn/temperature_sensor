#ifndef E56756F2_FCE9_4506_8291_7FDAF2C00E14
#define E56756F2_FCE9_4506_8291_7FDAF2C00E14

#include <algorithm>
#include <array>
#include <span>

template <class Item, std::size_t Size>
class ringbuffer final {
 public:
  using size_t = std::size_t;

  size_t size() const noexcept { return write_size; }

  using span_t = std::span<Item, Size>;

  void write(const Item& item) noexcept {
    write_position = (write_position + 1) % storage.size();
    write_size = std::min(write_size + 1, storage.size());
  }

  span_t prepare_read(size_t size) noexcept {
    const auto start =
        (storage.size() + write_position - write_size) % storage.size();
    const auto capacity = std::min(this->write_size, storage.size() - start);
    return span_t{storage}.subspan(start, std::min(size, capacity));
  }

  void commit_read(size_t size) noexcept { write_size -= size; }

 private:
  size_t write_size;
  size_t write_position;
  std::array<Item, Size> storage;
};

#endif /* E56756F2_FCE9_4506_8291_7FDAF2C00E14 */
