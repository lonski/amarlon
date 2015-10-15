#ifndef OPENABLE_H
#define OPENABLE_H

#include <actor_feature.h>

namespace amarlon {

class Actor;
class Openable;
struct OpenableDescription;
typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;
typedef std::shared_ptr<Openable> OpenablePtr;
typedef std::unique_ptr<Openable> OpenableUPtr;

class Openable : public ActorFeature
{
public:  

  const static ActorFeature::Type featureType;  

  Openable();
  virtual ~Openable();

  static OpenablePtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType();
  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  virtual bool open(ActorPtr executor);
  virtual bool close(ActorPtr executor);

  virtual bool isClosed() const;
  virtual bool isLocked() const;
  virtual int getLockId() const;
  virtual int getScriptId() const;
  virtual bool lock();
  virtual bool unlock();

protected:
  bool _locked;
  int _lockId;
  int _scriptId;
  bool _closed;

  std::string getScriptPath() const;


};


}

#endif // OPENABLE_H
