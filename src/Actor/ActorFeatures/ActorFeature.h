#ifndef ACTORFEATURE_H
#define ACTORFEATURE_H

namespace amarlon {

class Actor;

class ActorFeature
{
public:
  enum FeatureType
  {
    FT_NULL,
    AI,
    OPENABLE,
    WEARER,
    CONTAINER,
    FIGHTER,
    PICKABLE,
    FT_END
  };

  ActorFeature();
  virtual ~ActorFeature() = 0;

  void setOwner(Actor* owner);
  virtual ActorFeature* clone() = 0;
  virtual bool isEqual(ActorFeature* rhs) = 0;

protected:
  Actor* _owner;

};

}

#endif // ACTORFEATURE_H
