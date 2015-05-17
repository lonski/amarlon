#ifndef OPENABLE_H
#define OPENABLE_H

#include "actor_feature.h"
#include "openable_type.h"
#include "data_gateways/actor_descriptions.h"

namespace amarlon {

class Actor;
class Openable;
typedef std::shared_ptr<Openable> OpenablePtr;

class Openable : public ActorFeature
{
public:  
  const static ActorFeature::Type featureType;

  Openable();
  ~Openable() {}

  static OpenablePtr create(OpenableType type);
  static OpenablePtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType();

  virtual bool open(ActorPtr executor) = 0;
  virtual bool close(ActorPtr executor) = 0;

  virtual bool lock();
  virtual bool unlock();
  bool isLocked() const;

  int getLockId() const;
  void setLockId(int getLockId);

protected:
  friend class ActorDB;
  bool _locked;
  int _lockId;

};


}

#endif // OPENABLE_H
