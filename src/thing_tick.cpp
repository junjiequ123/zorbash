//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_main.h"
#include "my_wid_console.h"
#include "my_thing.h"
#include "my_python.h"

bool Thing::achieve_goals_in_life (void)
{_
    //
    // Don't do stuff too often
    //
    if (!time_have_x_tenths_passed_since(get_tick_rate_tenths(),
                                         get_timestamp_last_tick())) {
        return false;
    }

    set_timestamp_last_tick(time_get_time_ms_cached());

    if (is_loggable_for_unimportant_stuff()) {
        log("achieve goals at tick %d, game tick %u",
            get_tick(), game->tick_current);
    }

    lifespan_tick();
    if (is_dead) {
        return true;
    }

    hunger_clock();
    if (is_dead) {
        return true;
    }

    water_tick();
    if (is_dead) {
        return true;
    }

    lava_tick();
    if (is_dead) {
        return true;
    }

    collision_check_do();
    if (is_dead) {
        return true;
    }

    //
    // Roll the dice and see if we do anything
    //
    if (!std::empty(get_idle_tick_dice_str())) {
        auto roll = get_idle_tick();
        if (get_tick() - get_tick_last_did_something() > (unsigned int)roll) {
            auto d = get_idle_tick_dice();
            py_call_void_fn(d.python_mod.c_str(),
                            d.python_func.c_str(),
                            id, (int)mid_at.x, (int)mid_at.y);
            set_tick_last_did_something(get_tick());
        }
    }

    //
    // If there is a next hop to go to, do it.
    //
    if (cursor_path_pop_next_and_move()) {
        return true;
    }

    //
    // If this thing has AI, it can try and reach goals
    //
    if (get_dmap_scent()) {
        ai_get_next_hop();
    } else {
        is_tick_done = true;
    }

    return true;
}

bool Thing::achieve_goals_in_death (void)
{_
    //
    // Don't do stuff too often
    //
    if (!time_have_x_tenths_passed_since(get_tick_rate_tenths(),
                                         get_timestamp_last_tick())) {
        return false;
    }

    set_timestamp_last_tick(time_get_time_ms_cached());

    if (is_loggable_for_unimportant_stuff()) {
        log("achieve death goals at tick %d, game tick %u",
            get_tick(), game->tick_current);
    }

    resurrect_tick();

    return true;
}

void Thing::collision_check_do (void)
{_
    if (!tp()->collision_check()) {
        return;
    }

    bool target_attacked = false;
    bool target_overlaps = false;
    if (collision_check_and_handle_at(&target_attacked,
                                      &target_overlaps)) {
        return;
    }

    if (target_attacked || target_overlaps) {
        move_finish();
        cursor_path_stop();
    }
}

void Thing::tick (void)
{_
    g_thing_callframes_depth = callframes_depth;

    if (unlikely(is_dead)) {
        if (unlikely(is_resurrectable())) {
            //
            // Tick on player move/change of the current tick
            //
            auto tick = get_tick();
            if (tick < game->tick_current) {
                is_tick_done = false;
                if (achieve_goals_in_death()) {
                    if (is_tick_done) {
                        incr_tick();
                    }
                }
            }
        }
        return;
    }

    update_interpolated_position();

    if (unlikely(is_dead)) {
        if (is_loggable_for_unimportant_stuff()) {
            log("tick; died");
        }
        return;
    }

    bool is_waiting_to_tick = false;

    //
    // Completed moving?
    //
    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        is_waiting_to_tick = true;
    }

    if (is_waiting_to_tick) {
        //
        // Tick on player move/change of the current tick
        //
        auto tick = get_tick();
        if (tick < game->tick_current) {
            is_tick_done = false;
            if (achieve_goals_in_life()) {
                if (is_tick_done) {
                    incr_tick();
                }
            }
        }
    }

    //
    // Could be dead here.
    //
}
