#ifndef B0C2451A_39DD_45FE_936B_A71581142D22
#define B0C2451A_39DD_45FE_936B_A71581142D22

class interaction;

class interaction_control {
 public:
  virtual void set(interaction& next) = 0;

 protected:
  ~interaction_control() = default;
};

#endif /* B0C2451A_39DD_45FE_936B_A71581142D22 */
