#ifndef ACTORFEATURE_H
#define ACTORFEATURE_H

#include <memory>
#include <map>

namespace amarlon {

class Actor;
class ActorFeature;
struct Description;

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::weak_ptr<Actor> ActorWPtr;
typedef std::shared_ptr<ActorFeature> ActorFeaturePtr;
typedef std::shared_ptr<Description> DescriptionPtr;

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
  virtual ~ActorFeature() = 0;
  static ActorFeaturePtr create(Type featureType, DescriptionPtr dsc);

  void setOwner(ActorWPtr owner);
  ActorWPtr getOwner() const;
  virtual ActorFeaturePtr clone() = 0;
  virtual bool isEqual(ActorFeaturePtr rhs) const = 0;
  virtual ActorFeature::Type getType() = 0;
  virtual std::string getDescription();
  virtual int update();
  virtual std::string debug(const std::string& = "\n") { return ""; }
  virtual void upgrade(DescriptionPtr) = 0;
  virtual DescriptionPtr toDescriptionStruct(ActorFeaturePtr cmp = nullptr);

protected:
  ActorWPtr _owner;

};

inline ActorFeature::Type operator++(ActorFeature::Type& x) { return x = (ActorFeature::Type)(std::underlying_type<ActorFeature::Type>::type(x) + 1); }
inline ActorFeature::Type operator*(ActorFeature::Type c) {return c;}
inline ActorFeature::Type begin(ActorFeature::Type) {return ActorFeature::Type::FT_NULL;}
inline ActorFeature::Type end(ActorFeature::Type)   {return ActorFeature::Type::FT_END;}

static std::map<ActorFeature::Type, std::string> ActorFeatureToStr {
  { ActorFeature::AI,          "Ai" },
  { ActorFeature::OPENABLE,    "Openable" },
  { ActorFeature::WEARER,      "Wearer" },
  { ActorFeature::INVENTORY,   "Inventory" },
  { ActorFeature::CHARACTER,   "Character" },
  { ActorFeature::PICKABLE,    "Pickable" },
  { ActorFeature::DESTROYABLE, "Destroyable" },
  { ActorFeature::TRAP,        "Trap" },
  { ActorFeature::TALKER,      "Talker" }
};

typedef std::map<ActorFeature::Type, ActorFeaturePtr> FeatureMap;

}

#endif // ACTORFEATURE_H
