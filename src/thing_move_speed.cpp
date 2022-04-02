//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include <algorithm>

int Thing::move_speed_total(void)
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = move_speed();
  prev = stat;
  if (stat) {
    dbg3("Move speed: %d", stat);
  }

  stat += move_speed_mod();
  if (stat != prev) {
    prev = stat;
    dbg3("Move speed: with mod (%s): %d", modifier_to_string(move_speed_mod()).c_str(), stat);
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->move_speed_total();
      if (stat != prev) {
        prev = stat;
        dbg3("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
             modifier_to_string(iter->move_speed_mod()).c_str(), stat);
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(iter)) {
          continue;
        }
        //
        // Things that are equipped must be equipped to get the benefit.
        // Other items give the benefit by just being carried.
        //
        if (iter->is_auto_equipped()) {
          continue;
        }
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->move_speed_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->move_speed_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->move_speed_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->move_speed_mod()).c_str(), stat);
        }
      }
    }
  }

  return stat;
}

int Thing::move_speed(void)
{
  TRACE_NO_INDENT();
  return (tp()->move_speed());
}

////////////////////////////////////////////////////////////////////////////
// move_speed_mod
////////////////////////////////////////////////////////////////////////////
int Thing::move_speed_mod(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->move_speed_mod);
  } else {
    return 0;
  }
}

int Thing::move_speed_mod_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->move_speed_mod = v);
  return n;
}

int Thing::move_speed_mod_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->move_speed_mod -= v);
  return n;
}

int Thing::move_speed_mod_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->move_speed_mod += v);
  return n;
}

int Thing::move_speed_mod_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->move_speed_mod--);
  return n;
}

int Thing::move_speed_mod_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->move_speed_mod++);
  return n;
}