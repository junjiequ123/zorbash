//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::health_boost (int v)
{_
    auto old_health = get_stats_health();
    auto new_health = old_health + v;
    auto max_health = get_stats_health_max();
    new_health = std::min(new_health, max_health);
    set_stats_health(new_health);

    if (new_health == max_health) {
        log("health boost %d, %d -> max(%d)", v, old_health, new_health);
    } else {
        log("health boost %d, %d -> %d", v, old_health, new_health);
    }
}
