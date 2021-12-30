//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_console.hpp"

//
// Python callback upon being tick
//
bool Thing::on_tick(void)
{
  auto on_tick = tp()->on_tick_do();
  if (std::empty(on_tick)) {
    return false;
  }

  auto t = split_tokens(on_tick, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    auto owner = get_top_owner();
    if (owner) {
      dbg("Call %s.%s(owner=%s, item=%s, %d, %d)", mod.c_str(), fn.c_str(), owner->to_string().c_str(),
          to_string().c_str(), (unsigned int) curr_at.x, (unsigned int) curr_at.y);
      return py_call_bool_fn(mod.c_str(), fn.c_str(), owner->id.id, id.id, (unsigned int) curr_at.x,
                             (unsigned int) curr_at.y);
    } else {
      dbg("Call %s.%s(item=%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (unsigned int) curr_at.x,
          (unsigned int) curr_at.y);
      return py_call_bool_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
    }
  }

  ERR("Bad on_tick call [%s] expected mod:function, got %d elems", on_tick.c_str(), (int) on_tick.size());
  return false;
}

void Thing::update_tick(void)
{
  set_tick_last_did_something(game->tick_current);
  set_tick_last_location_check(game->tick_current);
}

void Thing::achieve_goals_in_life(void)
{
  if (is_changing_level || is_falling || is_waiting_to_ascend_dungeon || is_waiting_to_descend_sewer ||
      is_waiting_to_descend_dungeon || is_waiting_to_ascend_sewer || is_waiting_to_leave_level_has_completed_fall ||
      is_the_grid) {
    return;
  }

  TRACE_NO_INDENT();

  //
  // Check torch counts
  //
  update_light_strength();

  //
  // Lifespan tick for carried torches must be before is_hidden check
  //
  lifespan_tick();
  if (is_dead) {
    return;
  }

  //
  // Check stats don't get too low
  //
  stats_tick();
  if (is_dead) {
    return;
  }

  //
  // Periodic health checks
  //
  hunger_clock_tick();
  if (is_dead) {
    return;
  }

  hunger_update();
  if (is_dead) {
    return;
  }

  //
  // Timeout enemies
  //
  enemies_tick();
  if (is_dead) {
    return;
  }

  //
  // Timeout goals
  //
  goal_penalty_tick();
  if (is_dead) {
    return;
  }

  //
  // Timeout enemies to avoid
  //
  avoid_tick();
  if (is_dead) {
    return;
  }

  buff_tick();
  if (is_dead) {
    return;
  }

  debuff_tick();
  if (is_dead) {
    return;
  }

  //
  // Apply poison damage
  //
  poison_tick();
  if (is_dead) {
    return;
  }

  //
  // Apply necrosis damage
  //
  necrosis_tick();
  if (is_dead) {
    return;
  }

  //
  // Check for impacts
  //
  if (collision_check_do()) {
    return;
  }
  if (is_dead) {
    return;
  }

  //
  // Roll the dice and see if we do anything
  //
  idle_check();
  if (is_dead) {
    return;
  }

  if (! is_player()) {
    if (try_to_escape()) {
      dbg("Try to escape");
      return;
    }

    if (is_able_to_jump()) {
      if ((int) pcg_random_range(0, 1000) < tp()->is_able_to_jump_randomly_chance_d1000()) {
        dbg("Try to randomly jump");
        if (! collision_obstacle(level->player)) {
          if (try_to_jump_towards_player()) {
            return;
          }
        } else {
          if (try_to_jump()) {
            return;
          }
        }
      }
    }
  }

  if (fire_at_target()) {
    return;
  }

  if (on_tick()) {
    return;
  }

  //
  // If this thing has AI, it can try and reach goals
  //
  if (is_monst()) {
    ai_get_next_hop();
    if (is_moving) {
      return;
    }
  }

  //
  // If there is a next hop to go to, do it.
  //
  if (is_player()) {
    //
    // Pop the next player move at the end of the game tick
    //
    if (maybe_aip() && get_aip()->move_path.empty()) {
      //
      // If resting, keep resting
      //
      if (get_infop()->monst_state == MONST_STATE_MOVING) {
        ai_change_state(MONST_STATE_IDLE, "move path is empty");
      }
    }
  } else {
    //
    // Pop the next monst move.
    //
    if (path_pop_next_move()) {
      dbg("Popped next move");
      return;
    }
  }
}

void Thing::achieve_goals_in_death(void)
{
  dbg("Achieve death goals at tick %u", game->tick_current);
  TRACE_AND_INDENT();

  resurrect_tick();
  update_tick();
}

//
// Returns true if we attacked something
//
bool Thing::collision_check_do(void)
{
  TRACE_NO_INDENT();

  if (! tp()->collision_check()) {
    return false;
  }

  bool target_attacked = false;
  bool target_overlaps = false;
  if (collision_check_and_handle_at(&target_attacked, &target_overlaps)) {
    return target_attacked;
  }

  if (target_attacked || target_overlaps) {
    move_finish();
    clear_move_path("Collision");
  }
  return target_attacked;
}

void Thing::tick(void)
{
  dbg("Tick %d", game->tick_current);
  TRACE_AND_INDENT();

  update_interpolated_position();

  //
  // Allow the same thing to hit us again
  //
  if (maybe_aip()) {
    get_aip()->recently_hit_by.clear();
  }

  if (unlikely(is_dead)) {
    //
    // Resurrect things unless that can do unless that has been disabled e.g. via minion manifestor death
    //
    if (! is_resurrection_blocked && is_resurrectable()) {
      //
      // Tick on player move/change of the current tick
      //
      achieve_goals_in_death();
    }

    IF_DEBUG3 { log("Tick; is dead"); }
    return;
  }

  if (unlikely(is_dead)) {
    IF_DEBUG3 { log("Tick; died"); }
    return;
  }

  //
  // Tick on player move/change of the current tick
  //
  achieve_goals_in_life();
  if (is_dead) {
    return;
  }

  if (is_monst() || is_player()) {
    if (curr_at == last_at) {
      incr_idle_count();
    } else {
      set_idle_count(0);
    }
  }
}
