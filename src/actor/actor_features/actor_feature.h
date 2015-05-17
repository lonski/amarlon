#ifndef ACTORFEATURE_H
#define ACTORFEATURE_H

#include <memory>
#include <map>

namespace amarlon {

class Actor;
class ActorFeature;
struct Description;

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<ActorFeature> ActorFeaturePtr;
typedef std::shared_ptr<Description> DescriptionPtr;

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
  static ActorFeaturePtr create(Type featureType, DescriptionPtr dsc);

  void setOwner(ActorPtr owner);
  ActorPtr getOwner();
  virtual ActorFeaturePtr clone() = 0;
  virtual bool isEqual(ActorFeaturePtr rhs) = 0;
  virtual ActorFeature::Type getType() = 0;

protected:
  ActorPtr _owner;

};

typedef std::map<ActorFeature::Type, ActorFeaturePtr> FeatureMap;

}

#endif // ACTORFEATURE_H
