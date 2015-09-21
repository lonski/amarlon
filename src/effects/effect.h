#ifndef EFFECT_H
#define EFFECT_H

#include <memory>
#include <vector>
#include <effect_type.h>
#include <actor_descriptions.h>
#include <target.h>

namespace amarlon {

class Actor;
class Effect;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Effect> EffectPtr;
typedef std::map<std::string, std::string> Params;

class Effect
{
public:
  Effect();
  virtual ~Effect();

  static EffectPtr create(EffectType type);
  static EffectPtr create(EffectDescriptionPtr dsc);
  static EffectPtr create(EffectDescription dsc);

  virtual EffectType getType() const = 0;
  virtual EffectPtr clone() = 0;
  virtual bool isEqual(EffectPtr rhs) = 0;

  /**
   * @brief Applies the effect on given target
   * @param executor - an actor who executes the effect
   * @param target - the target on whis effect is applied
   */
  virtual bool apply(ActorPtr executor, const Target& target) = 0;

  /**
   * @brief Removes the effect's non-permamrnet changes from the target
   * @param executor - an actor who is revoking the effect
   * @param target - the target from which the effect is going to be removed
   */
  virtual bool revoke(ActorPtr executor, const Target& target) = 0;

  /**
   * @brief Serialize all effect fields to key-value params.
   *        Used to serialize effect into XML file.
   * @return A map with field name and its value
   */
  virtual Params toParams() const = 0;

  /**
   * @brief Opposite to toParams
   */
  virtual void load(const Params& params) = 0;

  /**
   * @brief Effect duration. Use "-1" for permament effect.
   */
  virtual int  getTime() const = 0;
  virtual void setTime(int time) = 0;


};

}

#endif // EFFECT_H
