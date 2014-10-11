#ifndef PICKABLE_H
#define PICKABLE_H

class Actor;

class Pickable
{
public:
  Pickable();

  virtual bool pick(Actor* owner, Actor* picker);
  virtual Actor* drop(Actor* owner);
  virtual void use(Actor* owner, Actor* user);

};

#endif // PICKABLE_H
