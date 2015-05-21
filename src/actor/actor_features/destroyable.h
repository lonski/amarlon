#ifndef DESTROYABLE_H
#define DESTROYABLE_H

#include <memory>
#include <actor_feature.h>

namespace amarlon {

class Destroyable;
typedef std::shared_ptr<Destroyable> DestroyablePtr;

class Destroyable : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  static DestroyablePtr create(DescriptionPtr dsc);

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);
  virtual ActorFeature::Type getType();

  void destroy();

  Destroyable();
  ~Destroyable();

private:
  void dropInventory();
  void dropOnGround(ActorPtr item);

};

}

#endif // DESTROYABLE_H
