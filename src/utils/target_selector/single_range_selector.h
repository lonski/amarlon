#ifndef SINGLE_RANGE_SELECTOR_H
#define SINGLE_RANGE_SELECTOR_H

#include <target_selector.h>
#include <functional>
#include <target.h>

namespace amarlon {

class SingleRangeSelector : public TargetSelector
{
public:
    SingleRangeSelector(const std::string& selectionMessage = "Navigate to select a tile. Press [ESC] to cancel.");

    virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){return true;});

private:
    Target tStart;
    Target tEnd;

    void render();
    void initialize();
};

}

#endif // SINGLE_RANGE_SELECTOR_H
