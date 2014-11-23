#include "single_range_selector.h"
#include <cmath>
#include <engine.h>
#include <world/map.h>
#include <gui/gui.h>
#include <utils.h>

namespace amarlon {

SingleRangeSelector::SingleRangeSelector(int range, const std::string &selectionMessage)
    : TargetSelector(selectionMessage)
    , _range(range)
{
    initValues();
}

void SingleRangeSelector::initValues()
{
    _dx = 0;
    _dy = 0;
    _x = Actor::Player->getX();
    _y = Actor::Player->getY();
}

std::vector<Actor*> SingleRangeSelector::select(bool (*filterFun)(Actor*))
{
    initValues();

    bool accepted = false;
    TCOD_key_t key;
    while ( key.vk != TCODK_ESCAPE && !accepted )
    {
        Engine::instance().gui().setStatusMessage( _selectionMessage );
        TCODSystem::waitForEvent(TCOD_KEY_PRESSED, &key, NULL, true);

        int dx_tmp(0), dy_tmp(0);
        handleDirectionKey(key, dx_tmp, dy_tmp);

        int calculatedRange = round( sqrt( pow(_dx+dx_tmp,2) + pow(_dy+dy_tmp,2)) );
        if ( calculatedRange <= _range )
        {
            _dx += dx_tmp;
            _dy += dy_tmp;
            if ( _updateFunction != nullptr) _updateFunction();
        }

        render();
        if ( key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER ) accepted = true;
    }

    std::vector<Actor*> vec = Engine::instance().currentMap().getActors(_x+_dx, _y+_dy, filterFun);
    return accepted ? vec
                    : std::vector<Actor*>();
}

void SingleRangeSelector::render()
{
    Engine::instance().render();
    highlightCurrentTile();
    TCODConsole::root->flush();
}

void SingleRangeSelector::highlightCurrentTile()
{
    TCODColor fgcol = TCODConsole::root->getCharForeground(_x+_dx, _y+_dy);
    TCODColor bgcol = TCODConsole::root->getCharBackground(_x+_dx, _y+_dy);
    TCODConsole::root->setCharForeground(_x+_dx, _y+_dy, TCODColor::lerp(fgcol, TCODColor::yellow, 0.6));
    TCODConsole::root->setCharBackground(_x+_dx, _y+_dy, TCODColor::lerp(bgcol, TCODColor::yellow, 0.1));
}

int SingleRangeSelector::getRange() const
{
    return _range;
}

TargetSelector& SingleRangeSelector::setRange(int range)
{
    _range = range;
    return *this;
}

}
