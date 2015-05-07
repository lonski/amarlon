#ifndef ACTORFEATURE_H
#define ACTORFEATURE_H

#include <memory>
#include <map>

namespace amarlon {

class Actor;
struct Description;

class ActorFeature
{
public:
  enum Type
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
  static ActorFeature* create(Type featureType, Description* dsc);

  void setOwner(Actor* owner);
  virtual ActorFeature* clone() = 0;
  virtual bool isEqual(ActorFeature* rhs) = 0;
  virtual ActorFeature::Type getType() = 0;

protected:
  Actor* _owner;

};

typedef std::shared_ptr<ActorFeature> ActorFeaturePtr;
typedef std::map<ActorFeature::Type, ActorFeaturePtr> FeatureMap;

}

#endif // ACTORFEATURE_H
