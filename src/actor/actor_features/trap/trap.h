#ifndef TRAP_H
#define TRAP_H

#include <actor_feature.h>
#include <target.h>
#include <trap_id.h>
#include <actor.pb.h>

namespace amarlon {

class Actor;
class Trap;
struct TrapDescription;
typedef std::shared_ptr<TrapDescription> TrapDescriptionPtr;
typedef std::shared_ptr<Trap> TrapPtr;
typedef std::shared_ptr<Actor> ActorPtr;

class Trap : public ActorFeature
{
public:
  const static ActorFeature::Type FeatureType;

  static TrapPtr create(const TrapData& data);

  Trap();
  Trap(const Trap& rhs);
  virtual ~Trap();

  bool operator==(const Trap& rhs) const;
  Trap& operator=(const Trap& rhs);
  virtual const TrapData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType();
  virtual TrapId getId() const;

  virtual bool trigger(Target victim);

  virtual bool isArmed() const;
  virtual void setArmed(bool armed);

  virtual bool isDetected() const;
  virtual void setDetected(bool detected);

  virtual std::string getScript() const;
  virtual std::string getName() const;

  /**
   * @brief Describes how hard is to disarm this trap.
   */
  virtual int getDifficulty();

private:
  TrapData _data;

  Trap(const TrapData& data);

};

}

#endif // TRAP_H
