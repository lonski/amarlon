#ifndef SINGLE_RANGE_SELECTOR_H
#define SINGLE_RANGE_SELECTOR_H

#include <target_selector.h>

namespace amarlon {

class SingleRangeSelector : public TargetSelector
{
public:
    SingleRangeSelector(int range = 1, const std::string& selectionMessage = "Select a tile..");

    virtual std::vector<Actor*> select(bool (*filterFun)(Actor*) = nullptr);

    int getRange() const;
    TargetSelector &setRange(int range);

private:
    int _range;
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
