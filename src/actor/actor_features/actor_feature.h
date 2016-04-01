#ifndef ACTORFEATURE_H
#define ACTORFEATURE_H

#include <memory>
#include <map>

namespace google { namespace protobuf {
  class Message;
}}

namespace amarlon {

class Actor;
class ActorFeature;

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::weak_ptr<Actor>   ActorWPtr;
typedef std::shared_ptr<ActorFeature> ActorFeaturePtr;

class ActorFeature
{
public:
  enum Type
  {
    FT_NULL,
    AI,
    OPENABLE,
    WEARER,
    INVENTORY,
    CHARACTER,
    PICKABLE,
    DESTROYABLE,
    TRAP,
    TALKER,
    FT_END
  };

  ActorFeature();
  virtual ~ActorFeature();

  virtual const ::google::protobuf::Message& getDataPolymorphic() const = 0;
  virtual ActorFeature::Type getFeatureType() = 0;

  void setOwner(ActorWPtr owner);
  ActorWPtr getOwner() const;

  virtual int update();
  virtual std::string getDescription();
  virtual std::string debug(const std::string& = "\n");

protected:
  ActorWPtr _owner;

};

inline ActorFeature::Type operator++(ActorFeature::Type& x) { return x = (ActorFeature::Type)(std::underlying_type<ActorFeature::Type>::type(x) + 1); }
inline ActorFeature::Type operator*(ActorFeature::Type c) {return c;}
inline ActorFeature::Type begin(ActorFeature::Type) {return ActorFeature::Type::FT_NULL;}
inline ActorFeature::Type end(ActorFeature::Type)   {return ActorFeature::Type::FT_END;}

typedef std::map<ActorFeature::Type, ActorFeaturePtr> FeatureMap;

}

#endif // ACTORFEATURE_H
