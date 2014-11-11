#ifndef TARGETSELECTOR_H
#define TARGETSELECTOR_H

#include <vector>
#include <string>
#include <utils/selector_type.h>

namespace amarlon {

class Actor;
class Map;

class TargetSelector
{
public:
  TargetSelector(const std::string& selectionMessage = "");
  virtual ~TargetSelector() {}

  static TargetSelector* create(SelectorType type);

  virtual TargetSelector& setSelectionMessage(const std::string& msg);
  virtual std::vector<Actor*> select(Actor* executor, Map* map, bool (*filterFun)(Actor*) = nullptr) = 0;

protected:
  std::string _selectionMessage;

};

}

#endif // TARGETSELECTOR_H
