#ifndef A220E6CA_F628_4466_8237_5DB778B91556
#define A220E6CA_F628_4466_8237_5DB778B91556

class interaction_control;

class interaction {
 public:
  virtual bool start(
      interaction_control& control) = 0;  // if false, leave interaction loop

 protected:
  ~interaction() = default;
};

#endif /* A220E6CA_F628_4466_8237_5DB778B91556 */
