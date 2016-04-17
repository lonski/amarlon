#ifndef OPENABLE_H
#define OPENABLE_H

#include <actor_feature.h>
#include <openable_description.h>

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

  Openable(DescriptionPtr dsc = nullptr);
  virtual void upgrade(DescriptionPtr dsc);
  virtual DescriptionPtr toDescriptionStruct(ActorFeaturePtr cmp = nullptr);
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
  virtual int getLockLevel() const;
  virtual int getScriptId() const;
  virtual bool lock();
  virtual bool unlock();

  virtual std::string debug(const std::string &linebreak);

protected:
  bool _locked;
  int _lockId;
  int _lockLevel;
  int _scriptId;
  bool _closed;
  OpenableState _closedState;
  OpenableState _openedState;

  std::string getScriptPath() const;
  bool executeScript(const std::string& fun, ActorPtr executor);
  bool applyState(const OpenableState& state);


};


}

#endif // OPENABLE_H
