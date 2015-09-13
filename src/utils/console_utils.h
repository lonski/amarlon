#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <memory>
#include <libtcod.hpp>
#include <target.h>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

void highlightCircle(int range, Target center);
void highlightCell(uint32_t x, uint32_t y);
void setTile(uint32_t x, uint32_t y, char c, TCODColor color);
void renderPath(Target start, Target end);

}

#endif // CONSOLE_UTILS_H
