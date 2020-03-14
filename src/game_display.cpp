//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

void Game::update_map (void)
{_
    level->update_map();
}

void Game::display (void)
{_
    if (!level) {
        return;
    }

    if (level->map_changed) {
        static int last_done;
        if (time_have_x_secs_passed_since(1, last_done)) {
            level->map_changed = false;
            last_done = time_get_time_ms_cached();
            game->update_map();
        }
    }

    if (!level->minimap_valid) {
        level->update_minimap();
    }

    blit_fbo_bind(FBO_MAIN);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    //
    // thing_render_all must come before thing_move_all as it populates
    // all the things into the map for collisions.
    //
    thing_render_all();
    blit_fbo_unbind();

    thing_gc();
}
