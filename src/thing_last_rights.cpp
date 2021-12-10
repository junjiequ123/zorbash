//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_log.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::last_rites(Thingp defeater, const std::string &reason)
{
  TRACE_AND_INDENT();
  last_rites(defeater, reason.c_str());
}

//
// Lower level function than dead. Adds the thing to gc.
//
void Thing::last_rites(Thingp defeater, const char *reason)
{
  //
  // Check we're not in a death loop
  //
  if (is_dying) {
    return;
  }
  is_dying = true;

  dbg3("Destroy");
  TRACE_AND_INDENT();
  ///////////////////////////////////////////////////////////////
  // WARNING: defeater can be nullptr
  ///////////////////////////////////////////////////////////////
  auto is_corpse_currently = is_corpse();

  //
  // If already dead, do nothing
  //
  if (is_dead) {
    //
    // Unless it is already a corpse. In such a case, if a corpse is
    // eaten we want to remove it.
    //
    if (! is_corpse_currently) {
      return;
    }

    //
    // You only die once
    //
    if (is_player()) {
      return;
    }
  }

  //
  // Unequip weapons
  //
  FOR_ALL_EQUIP(e) { unequip("owner is dead", e, false); }

  //
  // If in a bag, get out of there!
  //
  auto immediate_owner = get_immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(this);
  }

  //
  // If a minion generator dies, kill all minions
  //
  if (defeater && is_minion_generator()) {
    destroy_minions(defeater);
  }

  if (defeater && is_spawner()) {
    destroy_spawned(defeater);
  }

  //
  // Set is_dead after the log message or we print it as dead
  //
  auto The = text_The();
  is_dead  = true;

  //
  // Resurrect unless say this was a minion and its manifestor died
  //
  if (! is_resurrection_blocked) {
    if (is_resurrectable()) {
      set_tick_resurrect_when(game->tick_current + get_resurrect());
    }
  }

  if (maybe_infop()) {
    //
    // So that slimes don't keep moving when dead
    //
    move_finish();

    //
    // Drop everything!
    //
    if (on_death_drop_all_items()) {
      dbg("Drop all items on death");
      drop_all();
      dbg("Dropped all items");
    }

    skill_remove_all();
    buff_remove_all();
    debuff_remove_all();
  }

  if (on_death_is_open()) {
    dbg("Defeated, now open");
    level_pop();
    is_open = true;
    level_push();
    auto p = level->player;
    if (p) {
      float distance = get_distance_to_player();
      if (is_door()) {
        if (defeater && defeater->is_fire()) {
          if (distance < 5) {
            TOPCON("The door burns through.");
          } else if (distance < DMAP_IS_PASSABLE) {
            TOPCON("The hear the crackling of burning wood.");
          } else {
            TOPCON("You smell smoke in the air.");
          }
        } else if (defeater && defeater->is_player()) {
          TOPCON("The door crashes open.");
        } else {
          if (distance <= 1) {
            TOPCON("You see the door crash open.");
          } else if (distance < DMAP_IS_PASSABLE) {
            TOPCON("The hear the noise of a door crashing open.");
          } else {
            TOPCON("The hear the distant noise of a door crashing open.");
          }
        }
        p->update_light();
      } else {
        //
        // e.g. treasure chest
        //
        if (defeater && defeater->is_fire()) {
          if (distance < 5) {
            TOPCON("%s burns.", text_The().c_str());
          } else {
            TOPCON("You smell smoke in the air.");
          }
        } else if (defeater && defeater->is_player()) {
          TOPCON("%s breaks open.", text_The().c_str());
        } else {
          if (distance <= 1) {
            TOPCON("You see %s crash open.", text_the().c_str());
          } else if (distance < DMAP_IS_PASSABLE) {
            TOPCON("The hear the noise of a %s crashing open.", short_text_a_or_an().c_str());
          } else {
            TOPCON("The hear the distant noise of %s crashing open.", short_text_a_or_an().c_str());
          }
        }
      }
    }
  }

  if (is_bleeder()) {
    int splatters = pcg_random_range(2, 10);
    for (int splatter = 0; splatter < splatters; splatter++) {
      auto tpp = tp_random_blood();
      (void) level->thing_new(tpp, mid_at);
      if (unlikely(! tpp)) {
        err("Could not place blood");
        break;
      }
    }
  }

  //
  // Add to the hiscore table?
  //
  if (is_player()) {
    //
    // Poor player
    //
    if (game->robot_mode) {
      if (defeater && defeater->is_acid()) {
        TOPCON("%%fg=red$RIP: Robot is dissolved to death %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_fire()) {
        TOPCON("%%fg=red$RIP: Robot is burnt to death %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_water()) {
        TOPCON("%%fg=red$RIP: Robot is drowned %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_necrotic_danger_level()) {
        TOPCON("%%fg=red$RIP: Robot is rotted to death %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_engulfer()) {
        TOPCON("%%fg=red$RIP: Robot is consumed %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_monst()) {
        TOPCON("%%fg=red$RIP: Robot is defeated %s.%%fg=reset$", reason);
      } else {
        TOPCON("%%fg=red$RIP: Robot is deactivated %s.%%fg=reset$", reason);
      }
    } else {
      if (defeater && defeater->is_acid()) {
        TOPCON("%%fg=red$RIP: You are dissolved to death %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_fire()) {
        TOPCON("%%fg=red$RIP: You are burnt to death %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_water()) {
        TOPCON("%%fg=red$RIP: You are drowned %s.", reason);
      } else if (defeater && defeater->is_necrotic_danger_level()) {
        TOPCON("%%fg=red$RIP: You are rotted to death %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_engulfer()) {
        TOPCON("%%fg=red$RIP: You are consumed %s.%%fg=reset$", reason);
      } else if (defeater && defeater->is_monst()) {
        TOPCON("%%fg=red$RIP: You are defeated %s.%%fg=reset$", reason);
      } else {
        TOPCON("%%fg=red$RIP: You are killed %s.%%fg=reset$", reason);
      }
    }
  }

  {
    auto on_death = on_death_do();
    if (! std::empty(on_death)) {
      auto t = split_tokens(on_death, '.');
      if (t.size() == 2) {
        auto        mod   = t[ 0 ];
        auto        fn    = t[ 1 ];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
          fn = fn.replace(found, 2, "");
        }

        dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_string().c_str());

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
      } else {
        ERR("Bad on_death call [%s] expected mod:function, got %d elems", on_death.c_str(), (int) on_death.size());
      }
    }
  }

  //
  // Add to the hiscore table?
  //
  if (is_player()) {
    //
    // Poor player
    //
    if (! get_score()) {
      incr_score(1);
    }

    if (game->config.hiscores.is_new_hiscore(this)) {
      if (game->robot_mode) {
        TOPCON("%%fg=yellow$New robo high score, %s place!%%fg=reset$", game->config.hiscores.place_str(this));
      } else {
        TOPCON("%%fg=yellow$New high score, %s place!%%fg=reset$", game->config.hiscores.place_str(this));
      }
      game->config.hiscores.add_new_hiscore(this, title(), reason);
    }

    level->map_follow_player = false;
    game->dead_select(reason);
  } else if (is_loggable()) {
    dbg("%s defeated dead, %s", The.c_str(), reason);
    if (defeater && (defeater != this)) {
      if (defeater->is_player()) {
        if (is_monst()) {
          if (is_undead()) {
            TOPCON("%%fg=white$%s is vanquished, %s.%%fg=reset$", The.c_str(), reason);
          } else {
            TOPCON("%%fg=white$%s is defeated, %s.%%fg=reset$", The.c_str(), reason);
          }
        } else {
          TOPCON("%s is destroyed %s.", The.c_str(), reason);
        }

        defeater->score_add(this);
      } else if (is_monst() && (get_distance_to_player() >= DMAP_IS_PASSABLE)) {
        if (is_undead()) {
          TOPCON("You hear a distant moan...");
        } else if (is_jelly()) {
          TOPCON("You hear a distant splat...");
        } else if (is_humanoid()) {
          TOPCON("You hear distant cursing...");
        } else if (is_meat()) {
          TOPCON("You hear the distant crunching of bones...");
        } else {
          TOPCON("You hear a distant shriek...");
        }
      }
    }
  }

  is_dying = false;

  if (is_corpse_currently) {
    //
    // Already a corpse
    //
    dbg("Already a corpse, clean it up");
    if (! get_tick_resurrect_when()) {
      if (is_bony()) {
        dbg("Can place final bones");
        auto tpp = tp_random_bones();
        if (tpp) {
          (void) level->thing_new(tpp, mid_at);
        }
      }
    }
  } else if (is_corpse_on_death()) {
    //
    // Leaves a corpse
    //
    dbg("Defeated, leaves corpse");
    level->set_is_corpse(mid_at.x, mid_at.y);

    if (i_set_is_monst) {
      i_set_is_monst = false;
      level->unset_is_monst(mid_at.x, mid_at.y);
    }
    return;
  }

  //
  // If this was blocking the way to the player, update that now
  //
  if (! level->is_being_destroyed) {
    if (is_obs_wall_or_door()) {
      level->request_dmap_to_player_update = true;
    }
  }

  level_pop();

  if (is_loggable()) {
    dbg("Defeated, need to garbage collect");
  }

  gc();
}