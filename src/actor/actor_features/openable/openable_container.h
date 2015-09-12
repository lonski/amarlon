#ifndef OPENABLECONTAINER_H
#define OPENABLECONTAINER_H

#include <memory>
#include "openable.h"

namespace amarlon {

class OpenableContainer;
typedef std::shared_ptr<OpenableContainer> OpenableInventoryPtr;

class OpenableContainer : public Openable
{
public:

  class Creator : public Openable::Creator
  {
  public:
    virtual OpenablePtr create(OpenableDescriptionPtr dsc);
  };

  OpenableContainer();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  virtual bool open(ActorPtr executor);
  virtual bool close(ActorPtr executor);

};

}

#endif // OPENABLECONTAINER_H
