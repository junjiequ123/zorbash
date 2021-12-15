//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"

bool Thing::is_enemy(Thingp attacker)
{
  TRACE_AND_INDENT();
  if (unlikely(! maybe_aip())) {
    return false;
  }

  if (get_aip()->enemies.find(attacker->id) != get_aip()->enemies.end()) {
    return true;
  }
  return false;
}

//
// Timeout enemies so we don't resent them forever.
//
void Thing::enemies_tick(void)
{
  TRACE_AND_INDENT();
  if (! maybe_aip()) {
    return;
  }

  for (auto &p : get_aip()->enemies) {
    auto attacker = level->thing_find_optional(p.first);
    if (! attacker) {
      get_aip()->enemies.erase(p.first);
      return;
    }

    if (--p.second > 0) {
      if (is_player() && game->robot_mode) {
        CON("Robot: enemy timeout %s (%d timeout)", attacker->to_string().c_str(), p.second);
      }
      continue;
    }

    if (attacker->is_dead) {
      if (is_player() && game->robot_mode) {
        CON("Robot: enemy remove as is dead: %s", attacker->to_string().c_str());
      }
      get_aip()->enemies.erase(p.first);
      return;
    }

    //
    // If far enough away start to forget this enemy
    //
    if (distance(attacker->curr_at, curr_at) > get_distance_avoid()) {
      if (is_player() && game->robot_mode) {
        CON("Robot: enemy remove as is far away: %s", attacker->to_string().c_str());
      }
      get_aip()->enemies.erase(p.first);
      return;
    }

    //
    // Be resentful a bit longer
    //
    if (is_player() && game->robot_mode) {
      CON("Robot: enemy persists a bit longer: %s", attacker->to_string().c_str());
    }
    p.second = pcg_random_range(0, 10);
  }
}

void Thing::add_enemy(Thingp attacker)
{
  TRACE_AND_INDENT();

  if (attacker == this) {
    return;
  }
  if (unlikely(! attacker->is_monst() && ! attacker->is_player())) {
    return;
  }
  if (unlikely(! is_monst() && ! is_player())) {
    return;
  }
  if (! ai_resent_count()) {
    return;
  }
  if (same_leader(attacker)) {
    return;
  }

  if (! get_aip()->enemies[ attacker->id ]) {
    if (is_player() && game->robot_mode) {
      CON("Robot: enemy add %s", attacker->to_string().c_str());
    } else {
      dbg("Add new enemy %s", attacker->to_string().c_str());
    }
    get_aip()->enemies[ attacker->id ] = ai_resent_count();
  } else {
    dbg("Increment old enemy %s", attacker->to_string().c_str());
    get_aip()->enemies[ attacker->id ] *= 2;

    if (get_aip()->enemies[ attacker->id ] > THING_AI_MAX_RESENT_COUNT) {
      get_aip()->enemies[ attacker->id ] = THING_AI_MAX_RESENT_COUNT;
    }
  }
}
