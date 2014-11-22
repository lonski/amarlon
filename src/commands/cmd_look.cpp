#include "cmd_look.h"
#include <utils/target_selector/single_range_selector.h>

namespace amarlon {

bool CmdLook::accept(TCOD_key_t &key)
{
    return key.vk == TCODK_CHAR && key.c == 'l';
}

void CmdLook::execute()
{
    //SingleRangeSelector selector(2,"Select a tile to inspect...");
    //selector.select();
    //TODO
}


}
