#ifndef OPENABLE_H
#define OPENABLE_H

#include "../ActorFeature.h"
#include "OpenableType.h"
#include "DataGateways/ActorDescriptions.h"

namespace amarlon {

class Actor;

class Openable : public ActorFeature
{
public:  
  Openable();
  ~Openable() {}

  static Openable* create(OpenableType type);
  static Openable* create(Description* dsc);

  virtual bool open(Actor* executor) = 0;
  virtual bool close(Actor* executor) = 0;

  virtual bool lock();
  virtual bool unlock();
  bool isLocked() const;
  void setLocked(bool locked);

  int getLockId() const;
  void setLockId(int getLockId);


protected:
  friend class ActorDB;
  bool _locked;
  int _lockId;

};

}

#endif // OPENABLE_H
