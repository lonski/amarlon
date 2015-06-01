#ifndef SELECTORTYPE_H
#define SELECTORTYPE_H

namespace amarlon {

enum class TargetType
{
  SINGLE_NEIGHBOUR, //single target in neighbouring tile
  SINGLE_RANGE,     //single target in any tile
  AREA_RANGE,       //multiple targets in circle with its center at any tile
  AREA_NEIGHBOUR,   //multiple targets in circle with its center at neighbouring tile
  SELF              //the actor who uses the effect
};

}

#endif // SELECTORTYPE_H
