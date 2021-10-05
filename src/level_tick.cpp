//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.h"
#include "my_depth.h"
#include "my_game.h"
#include "my_monst.h"
#include "my_player.h"
#include "my_ptrcheck.h"
#include "my_python.h"
#include "my_random.h"
#include "my_sdl.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_wid_actionbar.h"
#include "my_wid_console.h"

void Level::handle_all_pending_things(int group)
{
  for (auto &i : all_animated_things_pending_remove[ group ]) {
    all_animated_things[ group ].erase(i.first);
  }
  all_animated_things_pending_remove[ group ] = {};

  for (auto &i : all_animated_things_pending_add[ group ]) {
    all_animated_things[ group ].insert(i);
  }
  all_animated_things_pending_add[ group ] = {};
}

void Level::handle_all_pending_things(void)
{
  for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
    handle_all_pending_things(group);
  }
}

bool Level::tick(void)
{
  TRACE_AND_INDENT();
  // LOG("Tick");
  // TOPCON("monsts %d.", monst_count);

  if (! game->started) {
    return false;
  }

  if (ts_fade_in_begin) {
    return false;
  }

  if (! cursor) {
    cursor = thing_new("cursor", player->mid_at);
  }

  handle_all_pending_things();
  things_gc_if_possible();

  //
  // Update the player map if needed. It is quite slow.
  //
  if (request_dmap_to_player_update) {
    request_dmap_to_player_update = false;
    dmap_to_player_update();
  }

  //
  // A new game event has occurred?
  //
  if (! game->tick_requested.empty()) {
    game->tick_begin_now();

    FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL(this, t)
    {
      uint32_t tick_begin_ms = time_get_time_ms();
      t->tick();
      if ((time_get_time_ms() - tick_begin_ms) > THING_TICK_DURATION_TOO_LONG) {
        t->err("PERF: Thing took too long, tick duration %u ms, max %u ms", time_get_time_ms() - tick_begin_ms,
               THING_TICK_DURATION_TOO_LONG);
      }
    }
    FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL_END(this)
  }

  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    if (t->is_scheduled_for_jump_end) {
      t->is_scheduled_for_jump_end = false;
      t->jump_end();
    }
    if (t->is_scheduled_for_death) {
      t->is_scheduled_for_death = false;
      t->dead(t->get_dead_reason());
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)

  //
  // For all things that move, like monsters, or those that do not, like
  // wands, and even those that do not move but can be destroyed, like
  // walls. Omits things like floors, corridors, the grid; those that
  // generally do nothing or are hidden.
  //
  game->things_are_moving = false;

  static const int wait_count_max = THING_TICK_WAIT_TOO_LONG;
  static int       wait_count;
  wait_count++;

  //
  // Animate anything that needs it
  //
  for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
    FOR_ALL_ANIMATED_THINGS_LEVEL(this, group, t)
    {
      t->animate();
      t->update_interpolated_position();
      t->get_fall();

      //
      // We need to check all animated things are finished moving as they
      // may not intersect with all interactive things. i.e a carried
      // sword animation.
      //
      if (t->is_moving) {
        if (game->robot_mode) {
          if ((wait_count > wait_count_max) && ! game->things_are_moving) {
            t->con("Waiting on animated moving thing longer than expected: %s", t->to_dbg_string().c_str());
          }
          game->things_are_moving = true;
        } else if (! t->is_offscreen) {
          if ((wait_count > wait_count_max) && ! game->things_are_moving) {
            t->con("Waiting on animated moving thing longer than expected: %s", t->to_dbg_string().c_str());
          }
          game->things_are_moving = true;
        }
      }
    }
    FOR_ALL_ANIMATED_THINGS_LEVEL_END(this)

    FOR_ALL_ANIMATED_THINGS_LEVEL(this, group, t)
    {
      if (t->is_scheduled_for_death) {
        t->is_scheduled_for_death = false;
        t->dead(t->get_dead_reason());
      }
    }
    FOR_ALL_ANIMATED_THINGS_LEVEL_END(this)
  }

  game->tick_update();

  //
  // Update the cursor position. But only if the mouse has moved. So if the
  // player is moving via keyboard alone, we don't pollute the screen.
  //
  if ((wheel_x != 0) || (wheel_y != 0)) {
    cursor_move();
  } else if (! time_have_x_tenths_passed_since(10, wid_last_mouse_motion)) {
    cursor_move();
  }

  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    //
    // Wait for animation end. Only if the thing is onscreen
    //
    if (t->frame_count != game->frame_count) {
      t->is_offscreen = true;
    } else {
      t->is_offscreen = false;
    }

    t->update_interpolated_position();
    t->get_fall();

    //
    // Check if we finished moving above. If not, keep waiting.
    //
    if (t->is_moving) {
      if (game->robot_mode) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on moving thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      } else if (! t->is_offscreen) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on moving thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      }
    }

    //
    // Check if we finished moving above. If not, keep waiting.
    //
    if (t->is_jumping) {
      if (game->robot_mode) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on jumping thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      } else if (! t->is_offscreen) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on jumping thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      }
    }

    //
    // If falling we need to update the z depth and position; and wait.
    //
    if (t->is_falling) {
      if (game->robot_mode) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on falling thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      } else if (! t->is_offscreen) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on falling thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      }
    }

    //
    // Wait on dying thing?
    //
    if ((t->is_dead_on_end_of_anim() && ! t->is_dead)) {
      if (game->robot_mode) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on dying thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      } else if (! t->is_offscreen) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on dying thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      }
    }

    //
    // Wait on resurrecting thing?
    //
    if (t->is_alive_on_end_of_anim() && t->is_resurrecting) {
      if (game->robot_mode) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on resurrecting thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      } else if (! t->is_offscreen) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on resurrecting thing longer than expected: %s", t->to_dbg_string().c_str());
        }
        game->things_are_moving = true;
      }
    }

    auto weapon_id = t->get_weapon_id_use_anim();
    if (weapon_id.ok()) {
      auto w = thing_find(weapon_id);
      if (w && ! w->is_dead) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          w->con("Waiting on this");
          t->con("This is the owner");
        }
        game->things_are_moving = true;
      }
    }

    if (t->get_ts_flip_start() && ! t->is_dead) {
      if (game->robot_mode) {
        if ((wait_count > wait_count_max) && ! game->things_are_moving) {
          t->con("Waiting on flipping thing longer than expected: %s", t->to_dbg_string().c_str());
        }

        game->things_are_moving = true;

        //
        // Make sure offscreen animation occurs.
        //
        if (t->is_offscreen) {
          t->set_ts_flip_start(0);
        }
      }
    }

    if (t->is_waiting_to_leave_level_has_completed_fall) {
      t->fall_to_next_level();
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on waiting to fall thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }

    if (t->is_scheduled_for_death) {
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        t->con("Waiting on scheduled for death thing longer than expected: %s", t->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }

    //
    // Make sure weapons keep yp
    //
    auto o = t->weapon_get_carry_anim();
    if (o) {
      o->update_interpolated_position();
      o->get_fall();
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)

  if (fade_out_finished) {
    if (player && player->is_waiting_to_descend_dungeon) {
      if (! player->descend_dungeon()) {
        player->err("Failed to descend dungeon");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on descending player thing longer than expected: %s", player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_ascend_dungeon) {
      if (! player->ascend_dungeon()) {
        player->err("Failed to ascend dungeon");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on ascending player thing longer than expected: %s", player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_descend_sewer) {
      if (! player->descend_sewer()) {
        player->err("Failed to descend sewer");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on descending sewer player thing longer than expected: %s",
                    player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_ascend_sewer) {
      if (! player->ascend_sewer()) {
        player->err("Failed to ascend sewer");
      }
      if ((wait_count > wait_count_max) && ! game->things_are_moving) {
        player->con("Waiting on ascending sewer player thing longer than expected: %s",
                    player->to_dbg_string().c_str());
      }
      game->things_are_moving = true;
    }
    if (player && player->is_waiting_to_leave_level_has_completed_fall) {
      player->fall_to_next_level();
      game->things_are_moving = true;
    }
  }

  if (game->things_are_moving) {
    return false;
  }

  debug_path_clear();

  wait_count = 0;

  if (! game->robot_mode) {
    player_tick();
  }

  //
  // Stop rapid pickup/drop events if particles are still in progress
  // Don't move this priot to update_interpolated_position or see flicker
  // in jumping.
  //
  if (player && player->particle_anim_exists()) {
    return false;
  }

  //
  // The robot needs to be more deterministic and less loosy goosey
  //
  if (game->robot_mode) {
    //
    // No moving if weapons have not finished firing
    //
    if (all_projectiles.size()) {
      return false;
    }

    if (new_projectiles.size()) {
      return false;
    }

    if (all_lasers.size()) {
      return false;
    }

    if (new_lasers.size()) {
      return false;
    }

    if (all_internal_particles.size()) {
      return false;
    }

    if (new_internal_particles.size()) {
      return false;
    }

    if (all_external_particles.size()) {
      return false;
    }

    if (new_external_particles.size()) {
      return false;
    }
  }

  //
  // If things have stopped moving, perform location checks on where they
  // are now. This handles things like shoving a monst into a chasm. We do
  // location checks on the ends of moves, but this is a backup and will
  // also handle things that do not move, like a wand that is now on fire.
  //
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    //
    // Need to do this even for dead things, so corpses don't hover over
    // chasms.
    //
    t->location_check();
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)

  //
  // We've finished waiting on all things, bump the game tick.
  //
  bool tick_done = game->tick_end();

  if (tick_done) {
    handle_all_pending_things();
    things_gc_if_possible();
#if 0
    //
    // For debugging consistent randomness
    //
    float h = 0;
    FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t) {
      h += t->mid_at.x;
      h += t->mid_at.y;
      t->con("at %f,%f", t->mid_at.x, t->mid_at.y);
    } FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)
    CON("TICK %d hash %f random %d", game->tick_current, h, pcg_rand());
#endif
  }

  //
  // If the level has started, we can enter robot mode.
  //
  if (! ts_fade_in_begin) {
    if (game->robot_mode_requested != game->robot_mode) {
      game->robot_mode                = game->robot_mode_requested;
      game->robot_mode_tick_requested = true;
      wid_actionbar_robot_mode_update();
      if (game->robot_mode) {
        game->tick_begin("robot mode");
        BOTCON("Robot mode");
      } else {
        BOTCON("Robot mode off");
      }
    }
  }

  if (tick_done) {
    if (game->robot_mode) {
      if (game->robot_mode_tick_requested) {
        CON("Robot: tick requested");
        game->robot_mode_tick_requested = false;
        if (player) {
          if (game->robot_mode) {
            player->ai_tick();
          } else if (player->monst_aip->move_path.size()) {
            player->path_pop_next_move();
          }
        }
      }

      if (game->tick_requested.empty()) {
        CON("Robot: no new tick was requested");
        game->robot_mode_tick();
      } else {
        CON("Robot: a new tick was requested");
      }
    } else if (player) {
      if (game->robot_mode) {
        player->ai_tick();
      } else if (player->monst_aip->move_path.size()) {
        player->path_pop_next_move();
      }
    }
  }

  //
  // Only update robot mode if things have stopped moving so we get
  // consistent random behaviour.
  //
  if (! game->tick_requested.empty()) {
    return true;
  }

  return false;
}

void Level::sanity_check(void)
{
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      auto monst_count = 0;
      FOR_ALL_THINGS(this, t, x, y)
      {
        if (t->is_monst()) {
          monst_count++;
        }
      }
      FOR_ALL_THINGS_END()

      if (monst_count) {
        if (! is_monst(x, y)) {
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

void Level::update_all_ticks(void)
{
  TRACE_AND_INDENT();
  for (auto group = THING_GROUP_ALL; group < MAX_THING_GROUPS; group++) {
    for (auto &i : all_things_of_interest[ group ]) {
      auto t = i.second;
      t->update_tick();
    }
  }
}
