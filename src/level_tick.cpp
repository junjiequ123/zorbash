//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_sys.h"
#include "my_wid_console.h"
#include "my_random.h"
#include "my_thing.h"
#include "my_python.h"
#include "my_player.h"
#include "my_array_bounds_check.h"
#include "my_wid_actionbar.h"
#include "my_ptrcheck.h"

void Level::tick (void)
{_
    // LOG("Tick");
    // TOPCON("monsts %d.", monst_count);
    if (!game->started) {
        return;
    }

    //
    // Update the cursor position.
    //
    cursor_move();

    //
    // Allows for debugging
    //
    if (wid_console_window && wid_console_window->visible) {
        return;
    }

    // LOG("-");

    //
    // For all things that move, like monsters, or those that do not, like
    // wands, and even those that do not move but can be destroyed, like
    // walls. Omits things like floors, corridors, the grid; those that
    // generally do nothing or are hidden.
    //
    game->things_are_moving = false;
    FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t) {
        //
        // If something is still moving, do not progress any ticks.
        //
        if (t->get_timestamp_move_begin()) {
            if (t->get_tick() < game->tick_current - 2) {
                t->log("is lagging, time left %d",
                       t->get_timestamp_move_end() - time_get_time_ms_cached());
            }

            t->update_interpolated_position();

            //
            // Check if we finished moving above. If not, keep waiting.
            //
            if (t->get_timestamp_move_begin()) {
                game->things_are_moving = true;
                t->log("is moving");
            }
        }
    } FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)
_
    if (!game->robot_mode) {
        player_tick();
    }

    //
    // Stop rapid pickup/drop events if particles are still in progress
    // Don't move this priot to update_interpolated_position or see flicker
    // in jumping.
    //
    if (player && player->particle_anim_exists()) {
        return;
    }

    //
    // No moving if weapons have not finished firing
    //
    if (all_projectiles.size()) {
        return;
    }

    if (new_projectiles.size()) {
        return;
    }

    if (all_lasers.size()) {
        return;
    }

    if (new_lasers.size()) {
        return;
    }

    //
    // If things have stopped moving, perform location checks on where they
    // are now. This handles things like shoving a monst into a chasm. We do
    // location checks on the ends of moves, but this is a backup and will
    // also handle things that do not move, like a wand that is now on fire.
    //
    bool wait_for_end_of_game_tick = false;
    FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t) {
        t->location_check();
        if (t->is_dead) {
            continue;
        }
        t->tick();

        if (t->get_tick() < game->tick_current) {
            if (!wait_for_end_of_game_tick) {
                wait_for_end_of_game_tick = true;
                t->log("Has not finished tick yet");
            }
        }
    } FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)

    for (auto& i : pending_remove_all_interesting_things) {
        all_interesting_things.erase(i.first);
    }
    pending_remove_all_interesting_things = {};

    for (auto& i : pending_add_all_interesting_things) {
        all_interesting_things.insert(i);
    }
    pending_add_all_interesting_things = {};

    //
    // If we've finished waiting on all things, bump the game tick.
    //
    if (!wait_for_end_of_game_tick) {
        game->tick_end();
#if 0
        //
        // For debugging consistent randomness
        //
        uint32_t h = 0;
        FOR_ALL_INTERESTING_THINGS_ON_LEVEL(this, t) {
            h += (int)t->mid_at.x;
            h += (int)t->mid_at.y;
        } FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(this)
        CON("TICK %d hash %u", game->tick_current, h);
#endif
    }

    //
    // Only update robot mode if things have stopped moving so we get
    // consistent random behaviour.
    //
    if (game->tick_completed == game->tick_current) {
        if (game->robot_mode_requested != game->robot_mode) {
            LOG("Update robot mode");
            game->robot_mode = game->robot_mode_requested;
            wid_actionbar_robot_mode_update();
        }

        if (game->robot_mode_tick_requested) {
            game->robot_mode_tick_requested = false;
            game->robot_mode_tick();
        }
    }
}

void Level::sanity_check (void)
{_
    for (auto x = 0; x < MAP_WIDTH; x++) {
	for (auto y = 0; y < MAP_HEIGHT; y++) {
            auto monst_count = 0;
	    FOR_ALL_THINGS(this, t, x, y) {
		if (t->is_monst()) {
                    monst_count++;
		}
	    } FOR_ALL_THINGS_END()

            if (monst_count) {
                if (!is_monst(x, y)) {
                    DIE("Level sanity fail. monst count exists, but no monster found, at %d,%d", x, y);
                }
            } else {
                if (is_monst(x, y)) {
                    DIE("Level sanity fail. no monst count exists, but monster found, at %d,%d", x, y);
                }
            }
	}
    }
}

void Level::update_all_ticks (void)
{_
    for (auto& i : all_interesting_things) {
        auto t = i.second;
        t->update_tick();
    }
}
