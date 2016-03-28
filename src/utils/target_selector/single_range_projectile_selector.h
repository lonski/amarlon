#ifndef SINGLE_RANGE_FILTER_SELECTOR_H
#define SINGLE_RANGE_FILTER_SELECTOR_H

#include <target_selector.h>
#include <libtcod.hpp>
#include <memory>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

class SingleRangeProjectileSelector : public TargetSelector
{
public:
    SingleRangeProjectileSelector(const std::string& selectionMessage = "Press [TAB] to change target. Press [ESC] to cancel.");

    virtual Target select(std::function<bool (amarlon::ActorPtr)> filterFun = [](ActorPtr){return true;});

private:
    Target tStart;
    Target tEnd;
    MapPtr _map;

    void render();
    void initialize();

};

}

#endif // SINGLE_RANGE_FILTER_SELECTOR_H
