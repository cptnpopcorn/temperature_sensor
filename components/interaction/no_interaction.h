#ifndef BC1286B0_E6FE_40A0_9F06_3DDC0193BB66
#define BC1286B0_E6FE_40A0_9F06_3DDC0193BB66

#include "interaction.h"

class no_interaction final : public interaction {
 public:
  static no_interaction instance;
  void start(interaction_control& control) override;
};

#endif /* BC1286B0_E6FE_40A0_9F06_3DDC0193BB66 */
