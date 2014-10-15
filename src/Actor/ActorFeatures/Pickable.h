#ifndef PICKABLE_H
#define PICKABLE_H

class Actor;

class Pickable
{
public:
  Pickable();
  virtual ~Pickable() {}
  void setOwner(Actor* owner);

  virtual bool pick(Actor* picker);
  virtual Actor* drop();
  virtual void use(Actor* user);

private:
  Actor* _owner;

};

#endif // PICKABLE_H
