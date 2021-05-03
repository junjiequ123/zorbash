// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_monst.h"
#include "my_thing_template.h"
#include "my_wid_console.h"
#include "my_player.h"
#include "my_array_bounds_check.h"
#include "my_wid_thing_info.h"
#include "my_sdl.h"
#include "my_ptrcheck.h"

void player_tick (void)
{_
    //
    // Trying to move when the console is visible.
    //
    if (wid_console_window && wid_console_window->visible) {
        if (g_opt_debug4) {
            LOG("Player tick; ignore, console open");
        }
        return;
    }

    //
    // Trying to move when moving items?
    //
    switch (game->state) {
        case Game::STATE_NORMAL:
            break;
        case Game::STATE_MOVING_ITEMS:     // Currently managing inventory
            if (g_opt_debug4) {
                LOG("Ignore player action when moving items");
            }
            return;
        case Game::STATE_COLLECTING_ITEMS: // Collecting en masse from the level
            if (g_opt_debug4) {
                LOG("Ignore player action when collectin items");
            }
            return;
        case Game::STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
            if (g_opt_debug4) {
            }
            LOG("Ignore player action when choosing target");
            return;
    }

    auto level = game->level;
    if (!level) {
        if (g_opt_debug4) {
            LOG("Player tick; ignore, no level");
        }
        return;
    }

    auto player = level->player;
    if (!player) {
        if (g_opt_debug4) {
            LOG("Player tick; ignore, no player");
        }
        return;
    }

    //
    // Trying to scroll the map?
    //
    const float map_move_scroll_delta = 0.2;
    const uint8_t *state = SDL_GetKeyboardState(0);

    if (state[game->config.key_map_left]) {
        level->map_wanted_at.x -= map_move_scroll_delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
    }

    if (state[game->config.key_map_right]) {
        level->map_wanted_at.x += map_move_scroll_delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
    }

    if (state[game->config.key_map_up]) {
        level->map_wanted_at.y -= map_move_scroll_delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
    }

    if (state[game->config.key_map_down]) {
        level->map_wanted_at.y += map_move_scroll_delta;
        level->cursor_needs_update = true;
        level->cursor_found = false;
        level->map_follow_player = false;
    }

    if (player->is_dead || player->is_hidden) {
        if (g_opt_debug4) {
            LOG("Player tick; ignore, is dead");
        }
        return;
    }

    static uint32_t last_key_pressed_when;
    if (!last_key_pressed_when) {
        last_key_pressed_when = time_get_time_ms_cached();
    } else if (time_get_time_ms_cached() - last_key_pressed_when < THING_MOVE_SPEED_MS) {
        return;
    }

    static bool left = false;
    static bool right = false;
    static bool up = false;
    static bool down = false;

    if (state[game->config.key_move_left]) {
        left = true;
    }

    if (state[game->config.key_move_right]) {
        right = true;
    }

    if (state[game->config.key_move_up]) {
        up = true;
    }

    if (state[game->config.key_move_down]) {
        down = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_UP)) {
        up = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN)) {
        down = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT)) {
        left = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT)) {
        right = true;
    }

    if (sdl_joy_axes) {
        if (sdl_joy_axes[3] > sdl_joy_deadzone) {
            right = true;
        }

        if (sdl_joy_axes[3] < -sdl_joy_deadzone) {
            left = true;
        }

        if (sdl_joy_axes[4] > sdl_joy_deadzone) {
            down = true;
        }

        if (sdl_joy_axes[4] < -sdl_joy_deadzone) {
            up = true;
        }

        if (sdl_joy_axes[0] > sdl_joy_deadzone) {
            right = true;
        }

        if (sdl_joy_axes[0] < -sdl_joy_deadzone) {
            left = true;
        }

        if (sdl_joy_axes[1] > sdl_joy_deadzone) {
            down = true;
        }

        if (sdl_joy_axes[1] < -sdl_joy_deadzone) {
            up = true;
        }
    }

    uint8_t attack = 0;
    uint8_t wait   = 0;
    uint8_t jump   = 0;

    attack = state[game->config.key_attack] ? 1 : 0;
    wait   = state[game->config.key_wait_or_collect] ? 1 : 0;
    jump   = state[game->config.key_jump] ? 1 : 0;

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_UP)) {
        up = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN)) {
        down = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT)) {
        left = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT)) {
        right = true;
    }

    if (get(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE)) {
        attack = true;
    }

    if (sdl_joy_axes) {
        if (sdl_joy_axes[3] > sdl_joy_deadzone) {
            right = true;
        }

        if (sdl_joy_axes[3] < -sdl_joy_deadzone) {
            left = true;
        }

        if (sdl_joy_axes[4] > sdl_joy_deadzone) {
            down = true;
        }

        if (sdl_joy_axes[4] < -sdl_joy_deadzone) {
            up = true;
        }

        if (sdl_joy_axes[0] > sdl_joy_deadzone) {
            right = true;
        }

        if (sdl_joy_axes[0] < -sdl_joy_deadzone) {
            left = true;
        }

        if (sdl_joy_axes[1] > sdl_joy_deadzone) {
            down = true;
        }

        if (sdl_joy_axes[1] < -sdl_joy_deadzone) {
            up = true;
        }
    }

    double d = 1.0;
    double dx = 0.0;
    double dy = 0.0;

    if (left) {
        dx = -d;
    }
    if (right) {
        dx = d;
    }
    if (up) {
        dy = -d;
    }
    if (down) {
        dy = d;
    }

    //
    // If things are almost done, then we can allow the player to move
    // as it looks smoother
    //
    // Do this after saving the key states above else we can miss keys.
    //
    if (game->things_are_moving) {
        bool wait = false;
        FOR_ALL_INTERESTING_THINGS_ON_LEVEL(level, t) {
            if (t->get_timestamp_move_begin()) {
                int time_left = t->get_timestamp_move_end() - time_get_time_ms_cached();
                if (time_left > 10) {
                    t->con("Player delayed due to me (%d left)",
                           t->get_timestamp_move_end() - time_get_time_ms_cached());
                    wait = true;
                    break;
                }
            }
        } FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(level)

        if (wait) {
            LOG("Player move delayed while things are moving");
            return;
        }

        //
        // This is a bit of a hack; but the tick is almost done and we
        // want the game to be smooth.
        //
        game->tick_end();
    }

    if (jump) {
        last_key_pressed_when = time_get_time_ms_cached();
        game->tick_begin("player jumped");
        player->log("Jump");

        if (game->cursor_move_path.size()) {
            //
            // A path to the target exists.
            //
            for (auto i = game->cursor_move_path.rbegin();
                 i != game->cursor_move_path.rend(); i++) {
                auto p = *i;
                if (player->try_to_jump(make_point(p.x, p.y))) {
                    game->cursor_move_path.clear();
                    break;
                }
            }
        } else if (level->cursor->mid_at == player->mid_at) {
            auto player_move_delta = player->dir_to_direction();
            point p = make_point(player->mid_at.x + player_move_delta.x,
                                 player->mid_at.y + player_move_delta.y);
            if (level->is_movement_blocking_hard(p.x, p.y) ||
                level->is_movement_blocking_soft(p.x, p.y)) {
                player->try_to_jump(make_point(player->mid_at));
            } else {
                player->try_to_jump(p);
            }
        } else if (level->cursor) {
            point p = make_point(level->cursor->mid_at.x,
                                 level->cursor->mid_at.y);
            if (level->is_movement_blocking_hard(p.x, p.y) ||
                level->is_movement_blocking_soft(p.x, p.y)) {
                player->try_to_jump(make_point(player->mid_at));
            } else {
                player->try_to_jump(p);
            }
        }
        player->monstp->move_path.clear();
        game->cursor_move_path.clear();
        level->cursor_path_clear();
    } else if (up || down || left || right || attack || wait) {
        last_key_pressed_when = time_get_time_ms_cached();

        if (attack) {
            player->log("Player attack");
        } else if (wait) {
            player->log("Player collect or wait");
        } else {
            player->log("Player move attempt");
        }
        _

        //
        // If we move manually, clear the path as it visually gets
        // in the way
        //
        level->cursor_path_clear();

        //
        // If swinging, don't leave the weapon behind
        //
        // Not sure about this one
        // if (player->get_weapon_id_use_anim().ok()) {
        //     player->topcon("Don't move while swinging weapon");
        //     return;
        // }

        //
        // IF something was being described and we moved, clear it now
        //
        wid_thing_info_fini();

        fpoint future_pos = player->mid_at + fpoint(dx, dy);
        player->move(future_pos, up, down, left, right, attack, wait, true);

        //
        // Update reachability for the player
        //
        level->player_dmap_update();
    }

    left = false;
    right = false;
    up = false;
    down = false;
}
