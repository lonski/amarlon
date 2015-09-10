#ifndef SINGLE_RANGE_SELECTOR_H
#define SINGLE_RANGE_SELECTOR_H

#include <target_selector.h>
#include <functional>

namespace amarlon {

class SingleRangeSelector : public TargetSelector
{
public:
    SingleRangeSelector(const std::string& selectionMessage = "Select a tile...");

    virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){return true;});

private:
    int _dx;
    int _dy;
    int _x;
    int _y;

    void render();
    void initValues();
    void highlightCurrentTile();
};

}

#endif // SINGLE_RANGE_SELECTOR_H
