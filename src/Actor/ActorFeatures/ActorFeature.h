#ifndef ACTORFEATURE_H
#define ACTORFEATURE_H

class Actor;

class ActorFeature
{
public:
  ActorFeature();
  virtual ~ActorFeature() = 0;

  void setOwner(Actor* owner);

protected:
  Actor* _owner;

};

#endif // ACTORFEATURE_H
