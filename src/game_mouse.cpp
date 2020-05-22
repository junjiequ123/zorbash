//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"

uint8_t
game_mouse_down (int32_t x, int32_t y, uint32_t button)
{_
    if (!game || !game->started || !world || !level->player) {
        return (false);
    }

    //
    // Grab the current move path and start walking toward it. This will
    // consume one move by the player.
    //
    level->player->cursor_path_pop_first_move();

    //
    // Close enough to attack?
    //
    if ((std::abs(level->player->mid_at.x - level->cursor->mid_at.x) <= 1) &&
        (std::abs(level->player->mid_at.y - level->cursor->mid_at.y) <= 1)) {
        int x = level->cursor->mid_at.x;
        int y = level->cursor->mid_at.y;
        FOR_ALL_INTERESTING_THINGS(level, t, x, y) {
            if (t != level->player) {
                level->player->attack(level->cursor->mid_at);
                return (true);
            }
        }
        FOR_ALL_THINGS_END()
    }
    return (false);
}

uint8_t
game_mouse_up (int32_t x, int32_t y, uint32_t button)
{_
    if (!game) {
        return (false);
    }

    return (false);
}
