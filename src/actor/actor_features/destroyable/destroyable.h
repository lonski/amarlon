#ifndef DESTROYABLE_H
#define DESTROYABLE_H

#include <memory>
#include <vector>
#include <actor_feature.h>
#include <actor.pb.h>

namespace amarlon {

class Destroyable;
typedef std::shared_ptr<Destroyable> DestroyablePtr;

class Destroyable : public ActorFeature
{
public:
  const static ActorFeature::Type FeatureType;

  static DestroyablePtr create(const DestroyableData &data);

  Destroyable();
  Destroyable(const Destroyable& rhs);
  virtual ~Destroyable();

  bool operator==(const Destroyable& rhs) const;
  Destroyable& operator=(const Destroyable& rhs);
  virtual const DestroyableData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType();

  void destroy();

private:
  DestroyableData _data;

  Destroyable(const DestroyableData& data);
  void dropInventory();
  void dropOnGround(ActorPtr item);
  void processDropRules();

};

}

#endif // DESTROYABLE_H
