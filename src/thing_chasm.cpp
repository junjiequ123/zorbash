//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::chasm_tick (void)
{_
    if (owner_get()) {
        return false;
    }

    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend || 
        is_waiting_to_descend || 
        is_waiting_to_fall || 
        is_jumping) { 
        return true;
    }

    if (is_floating()) {
        return false;
    }

    if (level->is_chasm(mid_at.x, mid_at.y)) {
        log("over a chasm");
        fall(1, 750);
        wobble(360);
        return true;
    }

    return false;
}
