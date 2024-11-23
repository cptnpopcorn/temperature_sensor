#ifndef A220E6CA_F628_4466_8237_5DB778B91556
#define A220E6CA_F628_4466_8237_5DB778B91556

class interaction_control;

class interaction {
 public:
  virtual void start(interaction_control&) = 0;

 protected:
  ~interaction() = default;
};

#endif /* A220E6CA_F628_4466_8237_5DB778B91556 */
