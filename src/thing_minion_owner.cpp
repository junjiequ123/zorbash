//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

float Thing::get_distance_from_minion_owner(void)
{
  auto manifestor = get_top_minion_owner();
  if (! manifestor) {
    return -1;
  }

  return distance(mid_at, manifestor->mid_at);
}

float Thing::get_distance_from_minion_owner(point p)
{
  auto manifestor = get_top_minion_owner();
  if (! manifestor) {
    return -1;
  }

  return distance(p, manifestor->mid_at);
}

bool Thing::too_far_from_minion_owner(void)
{
  auto manifestor = get_top_minion_owner();
  if (! manifestor) {
    return false;
  }

  if (distance(mid_at, manifestor->mid_at) > get_distance_minion_leash()) {
    return true;
  }
  return false;
}

bool Thing::too_far_from_minion_owner(point p)
{
  auto manifestor = get_top_minion_owner();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->mid_at) > get_distance_minion_leash()) {
    con("TODO %d,%d is dist %f vs %f too far", p.x, p.y, distance(p, manifestor->mid_at),
        get_distance_minion_leash());
    return true;
  }
  con("TODO %d,%d is dist %f vs %f ok", p.x, p.y, distance(p, manifestor->mid_at), get_distance_minion_leash());
  return false;
}

bool Thing::too_far_from_minion_owner(point p, float delta)
{
  auto manifestor = get_top_minion_owner();
  if (! manifestor) {
    return false;
  }

  if (distance(p, manifestor->mid_at) > get_distance_minion_leash() + delta) {
    return true;
  }
  return false;
}

Thingp Thing::get_top_minion_owner(void)
{
  TRACE_AND_INDENT();
  auto id = get_immediate_minion_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    if (unlikely(i->get_immediate_minion_owner_id().ok())) {
      return i->get_immediate_minion_owner();
    }
    return i;
  } else {
    return nullptr;
  }
}

Thingp Thing::get_immediate_minion_owner(void)
{
  TRACE_AND_INDENT();
  auto id = get_immediate_minion_owner_id();
  if (likely(id.ok())) {
    auto i = level->thing_find(id);
    if (unlikely(! i)) {
      return nullptr;
    }
    return i;
  } else {
    return nullptr;
  }
}

void Thing::set_minion_owner(Thingp minion_owner)
{
  TRACE_AND_INDENT();
  if (minion_owner) {
    verify(MTYPE_THING, minion_owner);
  }

  auto old_minion_owner = get_immediate_minion_owner();
  if (old_minion_owner) {
    if (old_minion_owner == minion_owner) {
      return;
    }

    if (minion_owner) {
      dbg("Will change minion owner %s->%s", old_minion_owner->to_string().c_str(),
          minion_owner->to_string().c_str());
    } else {
      dbg("Will remove minion owner %s", old_minion_owner->to_string().c_str());
    }
  } else {
    if (minion_owner) {
      dbg("Will set minion owner to %s", minion_owner->to_string().c_str());
    }
  }

  if (minion_owner) {
    set_minion_owner_id(minion_owner->id);
    minion_owner->incr_minion_count();
  } else {
    set_minion_owner_id(NoThingId);
    if (old_minion_owner) {
      old_minion_owner->decr_minion_count();
    }
  }
}

void Thing::remove_minion_owner(void)
{
  TRACE_AND_INDENT();
  auto old_minion_owner = get_immediate_minion_owner();
  if (! old_minion_owner) {
    err("No minion owner");
    return;
  }

  dbg("Remove minion owner %s", old_minion_owner->to_string().c_str());

  set_minion_owner_id(NoThingId);
  old_minion_owner->decr_minion_count();
}

//
// Defeat and detach all minions from their owner
//
void Thing::destroy_minions(Thingp defeater)
{
  TRACE_AND_INDENT();
  //
  // Warning defeater can be nullptr - e.g. when a generator falls to
  // a new level
  //

  if (! is_minion_generator()) {
    return;
  }

  if (! get_minion_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto minion = p.second;
      auto o      = minion->get_immediate_minion_owner();
      if (o && (o == this)) {
        minion->remove_minion_owner();
        minion->is_resurrection_blocked = true;
        minion->dead(defeater, "its manifestor died");
      }
    }
  }
}

//
// Detach all minions from their owner
//
void Thing::unleash_minions(void)
{
  TRACE_AND_INDENT();
  if (! is_minion_generator()) {
    return;
  }

  if (! get_minion_count()) {
    return;
  }

  //
  // Slow, but not used too often
  //
  FOR_ALL_THING_GROUPS(group)
  {
    for (auto p : level->all_things[ group ]) {
      auto minion = p.second;
      auto o      = minion->get_immediate_minion_owner();
      if (o && (o == this)) {
        minion->remove_minion_owner();
      }
    }
  }
}
