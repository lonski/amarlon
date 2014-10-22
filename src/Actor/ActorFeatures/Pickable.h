#ifndef PICKABLE_H
#define PICKABLE_H

#include <vector>
#include "ActorFeature.h"
#include "DataGateways/ActorDescriptions.h"

class Actor;
class Effect;

class Pickable : public ActorFeature
{
public:
  Pickable(bool stackable = false, int amount = 1);
  virtual ~Pickable() {}
  static Pickable* create(const PickableDescription& dsc);

  virtual bool use(Actor *executor, std::vector<Actor *> targets);
  virtual int getUsesCount() const;
  Actor* spilt(int amount);
  virtual ActorFeature* clone();

  int getAmount() const;
  void setAmount(int getAmount);
  bool isStackable() const;
  Effect *getEffect() const;
  void setEffect(Effect *getEffect);

private:
  bool _stackable;
  int _amount;
  Effect* _effect;

};

#endif // PICKABLE_H
