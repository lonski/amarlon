#ifndef KEY
#define KEY

#include <libtcod.hpp>
#include <cstring>

namespace amarlon {

struct Key : TCOD_key_t
{
  Key(TCOD_keycode_t code = TCODK_NONE)
  {
    memset(this, 0, sizeof(Key));
    vk = code;
  }
};

}

#endif // KEY

