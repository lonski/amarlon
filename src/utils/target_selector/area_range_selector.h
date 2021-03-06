#ifndef AREA_RANGE_SELECTOR_H
#define AREA_RANGE_SELECTOR_H

#include <target_selector.h>

namespace amarlon {

class AreaRangeSelector : public TargetSelector
{
public:
  AreaRangeSelector(const std::string& selectionMessage = "Navigate to select a tile. Press [ESC] to cancel.");

  virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){return true;});
  virtual void setRenderPath(bool renderPath);

private:
  Target tStart;
  Target tEnd;
  bool _renderPath;

  void initialize();
  void render();

};

}

#endif // AREA_RANGE_SELECTOR_H
