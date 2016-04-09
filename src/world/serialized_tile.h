#ifndef SERIALIZED_TILE_H
#define SERIALIZED_TILE_H

#include <stdint.h>

namespace amarlon {

struct SerializedTile
{
  uint8_t type;
  uint8_t flags;
};

}

#endif // SERIALIZED_TILE_H
