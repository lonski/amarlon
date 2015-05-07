#ifndef TARGETSELECTOR_H
#define TARGETSELECTOR_H

#include <vector>
#include <string>
#include <functional>
#include "utils/selector_type.h"

namespace amarlon {

class Actor;
class Map;

class TargetSelector
{
public:
  TargetSelector(const std::string& selectionMessage = "");
  virtual ~TargetSelector() {}

  static TargetSelector* create(SelectorType type);

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
  virtual std::vector<Actor*> select(std::function<bool (amarlon::Actor*)>* filterFun = nullptr) = 0;

protected:
  std::string _selectionMessage;
  std::function<void()> _updateFunction;

};

}

#endif // TARGETSELECTOR_H
