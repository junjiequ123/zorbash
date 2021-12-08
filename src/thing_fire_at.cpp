//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

typedef struct {
  Thingp target;
  int    priority;
} ThingPossibleHit;

#define MAX_THING_POSSIBLE_HIT 128
static ThingPossibleHit thing_possible_hits[ MAX_THING_POSSIBLE_HIT ];
static int              thing_possible_hit_size;

//
// Python callback upon being fire_at
//
bool Thing::on_firing_at_something(Thingp target)
{
  TRACE_AND_INDENT();
  auto on_firing_at_something = tp()->on_firing_at_something_do();
  if (std::empty(on_firing_at_something)) {
    return false;
  }

  auto t = split_tokens(on_firing_at_something, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), target->to_string().c_str());

    return py_call_bool_fn(mod.c_str(), fn.c_str(), id.id, target->id.id, (unsigned int) mid_at.x,
                           (unsigned int) mid_at.y);
  }

  ERR("Bad on_firing_at_something call [%s] expected mod:function, got %d elems", on_firing_at_something.c_str(),
      (int) on_firing_at_something.size());
  return false;
}

/*
 * Find the thing with the highest priority to hit.
 */
Thingp Thing::get_best_fire_at_target(void)
{
  ThingPossibleHit *best = nullptr;
  int               i;

  for (i = 0; i < thing_possible_hit_size; i++) {
    ThingPossibleHit *cand = &thing_possible_hits[ i ];

    if (! best) {
      best = cand;
      continue;
    }

    //
    // More dangerous things (to me) are preferred
    //
    cand->priority += get_danger_current_level(cand->target);

    //
    // Closer things are preferred
    //
    cand->priority -= DISTANCE(mid_at.x, mid_at.y, cand->target->mid_at.x, cand->target->mid_at.y);

    if (cand->priority > best->priority) {
      /*
       * If this target is higher prio, prefer it.
       */
      best = cand;
    }
  }

  thing_possible_hit_size = 0;
  if (! best) {
    return nullptr;
  }

  return best->target;
}

/*
 * Add a thing to the list of things that could be hit on this attack.
 */
static void thing_possible_hit_add(Thingp me, Thingp target)
{
  if (! get(me->get_aip()->can_see_currently.can_see, (int) target->mid_at.x, (int) target->mid_at.y)) {
    return;
  }

  if (thing_possible_hit_size >= MAX_THING_POSSIBLE_HIT) {
    return;
  }

  ThingPossibleHit *h = &thing_possible_hits[ thing_possible_hit_size++ ];
  memset(h, 0, sizeof(*h));
  h->target   = target;
  h->priority = target->collision_hit_priority();
}

//
// Try to find something to fire at.
//
bool Thing::fire_at_target(void)
{
  if (! is_able_to_fire_at()) {
    return false;
  }

  int   dx, dy;
  float distance = get_distance_vision();

  for (dx = -distance; dx <= distance; dx++)
    for (dy = -distance; dy <= distance; dy++) {

      int x = mid_at.x + dx;
      int y = mid_at.y + dy;

      //
      // Too far?
      //
      auto d = DISTANCE(x, y, mid_at.x, mid_at.y);
      if (d > distance) {
        continue;
      }

      //
      // Too close, use melee
      //
      if (d < 2) {
        continue;
      }

      FOR_ALL_THINGS_THAT_INTERACT(level, it, x, y)
      {
        if (this == it) {
          continue;
        }

        //
        // No point in shooting at the dead
        //
        if (it->is_dead) {
          continue;
        }

        //
        // No shooting at blood!
        //
        if (it->is_monst() || it->is_player()) {
          if (possible_to_attack(it)) {
            thing_possible_hit_add(this, it);
          }
        }
      }
      FOR_ALL_THINGS_END();
    }

  auto target = get_best_fire_at_target();
  if (! target) {
    return false;
  }

  return on_firing_at_something(target);
}

bool Thing::fire_at_and_choose_target(Thingp item)
{
  TRACE_AND_INDENT();
  if (item->laser_name().empty()) {
    return projectile_choose_target(item);
  } else {
    return laser_choose_target(item);
  }
}
