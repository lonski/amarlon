#ifndef ACTORFEATURE_H
#define ACTORFEATURE_H

class Actor;

class ActorFeature
{
public:
  ActorFeature();
  virtual ~ActorFeature() = 0;

  void setOwner(Actor* owner);
  virtual ActorFeature* clone() = 0;

protected:
  Actor* _owner;

};

#endif // ACTORFEATURE_H
