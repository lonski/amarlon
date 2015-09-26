#ifndef ANIMATION_H
#define ANIMATION_H

#include <target.h>
#include <memory>
#include <libtcod.hpp>
#include <animation_description.h>
#include <animation_type.h>

namespace amarlon {

typedef std::map<std::string, std::string> Params;

namespace animation {

class Animation;
typedef std::shared_ptr<Animation> AnimationPtr;

class Animation
{
public:
  Animation();
  virtual ~Animation();

  static AnimationPtr create(AnimationDescriptionPtr dsc);
  static AnimationPtr create(AnimationDescription dsc);
  static AnimationPtr create(Type type);
  virtual AnimationPtr clone() = 0;
  virtual void run() = 0;
  virtual Type getType() const = 0;

  /**
   * @brief Serialize all animation fields to key-value params.
   *        Used to serialize animation into XML file.
   * @return A map with field name and its value
   */
  virtual Params toParams() const = 0;

  /**
   * @brief Opposite to toParams
   */
  virtual void load(const Params& params) = 0;

  virtual void setLocation(const Target& startLoc, const Target& endLoc);
  virtual Target getStartLocation() const;
  virtual Target getEndLocation() const;

private:
  Target _start;
  Target _end;

};

}}

#endif // ANIMATION_H
