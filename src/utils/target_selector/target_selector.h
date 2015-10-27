#ifndef TARGETSELECTOR_H
#define TARGETSELECTOR_H

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <target_type.h>
#include <target.h>

namespace amarlon {

class Actor;
class Map;
class TargetSelector;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<TargetSelector> TargetSelectorPtr;

class TargetSelector
{
public:
  TargetSelector(const std::string& selectionMessage = "");
  virtual ~TargetSelector() {}

  static TargetSelectorPtr create(TargetType type);

  /**
   * @brief set the function wchih will be called each time, target selector updates
   *        in specific: when the target changes (the cursor moves)
   */
  virtual TargetSelector& setUpdateFunction(std::function<void()> fun);

  /**
   * @brief set the message wchih will be displayed at target selector activation
   *        for example "select door to open"
   */
  virtual TargetSelector& setSelectionMessage(const std::string& msg);

  /**
   * @brief starts the selection process
   * @param filter fun - filter for actor selection
   *        for example only alive monsters could be selected
   * @return array of selected actors
   */
  virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){ return true;} ) = 0;

  virtual void setRange(int range);
  virtual int getRange() const;
  virtual void setRadius(int radius);
  virtual int getRadius() const;

protected:
  std::string _selectionMessage;
  std::function<void()> _updateFunction;
  int _range;
  int _radius;

};

}

#endif // TARGETSELECTOR_H
