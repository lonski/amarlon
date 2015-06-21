#ifndef OPENABLE_H
#define OPENABLE_H

#include "actor_feature.h"
#include "openable_type.h"
#include "data_gateways/actor_descriptions.h"

namespace amarlon {

class Actor;
class Openable;
typedef std::shared_ptr<Openable> OpenablePtr;
typedef std::unique_ptr<Openable> OpenableUPtr;

class Openable : public ActorFeature
{
public:  

  class Creator
  {
  public:
    virtual ~Creator() {}
    virtual OpenablePtr create(OpenableDescriptionPtr dsc) = 0;

  protected:
    void fillCommonOpenablePart(OpenablePtr openable, OpenableDescriptionPtr dsc);

  };

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
  virtual bool isLocked() const;
  virtual void setLocked(bool locked);

  int getLockId() const;
  void setLockId(int getLockId);

protected:
  bool _locked;
  int _lockId;

};


}

#endif // OPENABLE_H
