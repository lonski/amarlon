#ifndef PICKABLE_H
#define PICKABLE_H

#include "ActorFeature.h"

class Actor;

class Pickable : public ActorFeature
{
public:
  Pickable(bool stackable = false, int amount = 1);
  virtual ~Pickable() {}

  virtual void use(Actor* user);
  Actor* spilt(int amount);

  int getAmount() const;
  void setAmount(int getAmount);
  bool isStackable() const;

private:
  bool _stackable;
  int _amount;

};

#endif // PICKABLE_H
