#ifndef C8DC5C6D_1CE8_46D0_ACA2_A7EFEFC6AAC0
#define C8DC5C6D_1CE8_46D0_ACA2_A7EFEFC6AAC0

#include <compressed_measurement.h>
#include <ringbuffer.h>

class measurement_traits final {
 public:
  using buffer_t = ringbuffer<compressed_measurement, 512>;
};

#endif /* C8DC5C6D_1CE8_46D0_ACA2_A7EFEFC6AAC0 */
