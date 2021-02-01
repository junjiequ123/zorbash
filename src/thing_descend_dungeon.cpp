//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::descend_dungeon_tick (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_descend_dungeon || 
        is_waiting_to_ascend_sewer || 
        is_waiting_to_fall || 
        is_jumping) { 
        return false;
    }

    if (get_immediate_owner()) {
        return false;
    }

    if (!is_able_to_change_levels()) {
        return false;
    }

    if (!level->is_descend_dungeon(mid_at.x, mid_at.y)) {
        return false;
    }

    if (get_tick() - get_tick_last_level_change() < 1) {
        return false;
    }

    if (is_player()) {
        level->timestamp_fade_out_begin = time_get_time_ms_cached();
        is_waiting_to_descend_dungeon = true;
        return true;
    } else {
        return descend_dungeon();
    }
}

bool Thing::descend_dungeon (void)
{_
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_fall || 
        is_jumping) { 
        return false;
    }

    if (!monstp) {
        return false;
    }

    if (is_monst()) {
        if (level->player) {
            //
            // Don't descend if player is on the same level
            //
            return false;
        }
    }

    //
    // No level change if too rapid
    //
    if (get_tick() - get_tick_last_level_change() < 1) {
        return false;
    }

    auto next_level = level->world_at + point3d(0, 0, 2);
    game->init_level(next_level);

    if (is_player()) {
        game->current_level = next_level;
    }

    log("Is trying to descend");

    auto l = get(game->world.levels, next_level.x, next_level.y, next_level.z);
    if (!l) {
        if (is_player()) {
            MINICON("The exit is permanently blocked!");
        }
        return false;
    }

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            if (l->is_ascend_dungeon(x, y)) {
                if (is_player()) {
                    game->level = l;
                    MINICON("You bravely descend");
                }

                log("Move to next level entrance");
                is_changing_level = true;

                level_change(l);
                set_tick_last_level_change(get_tick());
                move_to_immediately(fpoint(x, y));
                move_carried_items_immediately();
                if (is_player()) {
                    l->player = this;
                    l->scroll_map_to_player();
                    l->update();
                    //
                    // Make sure all monsts on the new level are at the
                    // same tick or they will get lots of free attacks
                    //
                    l->update_all_ticks();
                }

                move_finish();
                set_interpolated_mid_at(mid_at);
                update_interpolated_position();
                location_check();
                update_light();

                if (is_player()) {
                    level->cursor->move_to_immediately(mid_at);
                }

                is_changing_level = false;
                log("Moved to next level entrance");
                if (is_player()) {
                    level->timestamp_fade_in_begin = time_get_time_ms_cached();
                    level->update();
                }
                return true;
            }
        }
    }

    if (is_player()) {
        game->tick_begin("descend to new level");
        level->timestamp_fade_in_begin = time_get_time_ms_cached();
        level->update();
    }
    return true;
}