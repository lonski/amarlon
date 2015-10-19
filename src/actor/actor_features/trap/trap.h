#ifndef TRAP_H
#define TRAP_H

#include <actor_feature.h>
#include <target.h>
#include <trap_id.h>

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
  const static ActorFeature::Type featureType;

  Trap();
  virtual ~Trap();

  static TrapPtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType();
  virtual TrapId getId() const;

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

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
  TrapId _id;
  bool _armed;
  int _difficulty;
  bool _detected;

};

}

#endif // TRAP_H
