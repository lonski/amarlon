#ifndef OPENABLE_H
#define OPENABLE_H

#include <actor_feature.h>
#include <actor.pb.h>

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

  const static ActorFeature::Type FeatureType;

  static OpenablePtr create(const OpenableData& data);

  Openable();
  Openable(const Openable& rhs);
  virtual ~Openable();

  bool operator==(const Openable& rhs) const;
  Openable& operator=(const Openable& rhs);
  virtual const OpenableData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType();

  virtual bool open(ActorPtr executor);
  virtual bool close(ActorPtr executor);

  virtual bool isClosed() const;
  virtual bool isLocked() const;
  virtual int getLockId() const;
  virtual int getLockLevel() const;
  virtual int getScriptId() const;
  virtual bool lock();
  virtual bool unlock();

protected:
  OpenableData _data;

  Openable(const OpenableData& data);
  std::string getScriptPath() const;

};


}

#endif // OPENABLE_H
