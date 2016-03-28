#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#include <memory>
#include <libtcod.hpp>
#include <target.h>
#include <point.h>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

void highlightFilledCircle(int range, Target center, TCODColor color = TCODColor::lighterYellow * 0.1);
void highlightCell(uint32_t x, uint32_t y);
void setTile(uint32_t x, uint32_t y, char c, TCODColor color);
void setTile(const Point& p, char c, TCODColor color);
void renderPath(Target start, Target end);
void drawCircle(int radius, Target center, char c = '*', TCODColor color = TCODColor::red);

}

#endif // CONSOLE_UTILS_H
