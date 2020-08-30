//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

std::string Thing::to_string (void) const
{_
    auto tpp = tp();

    verify(this);
    verify(tpp);

    if (unlikely(!tpp)) {
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(<no tp>%s%s%s%s T%u @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id,
                               is_dead ? "/dead" : "",
                               is_hidden ? "/hidden" : "",
                               is_jumping ? "/jumping" : "",
                               is_falling ? "/falling" : "",
                               get_tick_const(),
                               mid_at.x, mid_at.y));
    } else if (get_stats_health_max()) {
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(%s%s%s%s%s T%u @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id, tpp->name().c_str(),
                               is_dead ? "/dead" : "",
                               is_hidden ? "/hidden" : "",
                               is_jumping ? "/jumping" : "",
                               is_falling ? "/falling" : "",
                               get_tick_const(),
                               mid_at.x, mid_at.y));
    } else {
        return (string_sprintf("L%d,%d,%d %" PRIx32 "(%s%s%s%s%s T%u @%g,%g)",
                               level->world_at.x,
                               level->world_at.y,
                               level->world_at.z,
                               id, tpp->name().c_str(),
                               is_dead ? "/dead" : "",
                               is_hidden ? "/hidden" : "",
                               is_jumping ? "/jumping" : "",
                               is_falling ? "/falling" : "",
                               get_tick_const(),
                               mid_at.x, mid_at.y));
    }
}

const char * Thing::to_cstring (void) const
{_
    return (to_string().c_str());
}
