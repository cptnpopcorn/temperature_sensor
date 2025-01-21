#ifndef B1B62D95_D9CC_4399_98E2_C702AD044475
#define B1B62D95_D9CC_4399_98E2_C702AD044475

#include <compressed_measurement.h>
#include <ringbuffer.h>

class app_traits final {
 public:
  using buffer_t = ringbuffer<compressed_measurement, 512>;
};

#endif /* B1B62D95_D9CC_4399_98E2_C702AD044475 */
