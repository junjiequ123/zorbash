//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_tile.h"
#include "my_tex.h"
#include "my_gl.h"
#include "my_thing.h"

void Level::display_fade_out (void)
{
    blit_fbo_bind(FBO_FADE);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    point at(game->config.inner_pix_width / 2, game->config.inner_pix_height / 2);
    if (player) {
        at = ((player->last_blit_tl + player->last_blit_br) / 2);
    }
    int lines = 1000;
    float step = RAD_360 / (float) lines;
    float ts = (float)(time_get_time_ms_cached() - timestamp_fade_out_begin) / LEVEL_FADE_OUT_MS;
    float rad = (1.0 - ts) * (float) game->config.inner_pix_width / 2;

    blit_init();

    int i;

    //
    // Walk the light rays in a circle.
    //
    push_point(at.x, at.y);

    for (float th = 0; th < RAD_360; th += step) {
        int16_t p1x = at.x + rad * cos(th);
        int16_t p1y = at.y + rad * sin(th);
        push_point(p1x, p1y);
    }

    //
    // Complete the circle with the first point again.
    //
    i = 0; {
        float th = 0;
        int16_t p1x = at.x + rad * cos(th);
        int16_t p1y = at.y + rad * sin(th);
        push_point(p1x, p1y);
    }

    blit_flush_triangle_fan();
    blit_fbo_unbind();
}

void Level::display_fade_in (void)
{
    blit_fbo_bind(FBO_FADE);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    point at(game->config.inner_pix_width / 2, game->config.inner_pix_height / 2);
    if (player) {
        at = ((player->last_blit_tl + player->last_blit_br) / 2);
    }

    int lines = 1000;
    float step = RAD_360 / (float) lines;
    float ts = (float)(time_get_time_ms_cached() - timestamp_fade_in_begin) / LEVEL_FADE_IN_MS;
    float rad = ts * (float) game->config.inner_pix_width / 2;

    blit_init();

    int i;

    //
    // Walk the light rays in a circle.
    //
    push_point(at.x, at.y);

    for (float th = 0; th < RAD_360; th += step) {
        int16_t p1x = at.x + rad * cos(th);
        int16_t p1y = at.y + rad * sin(th);
        push_point(p1x, p1y);
    }

    //
    // Complete the circle with the first point again.
    //
    i = 0; {
        float th = 0;
        int16_t p1x = at.x + rad * cos(th);
        int16_t p1y = at.y + rad * sin(th);
        push_point(p1x, p1y);
    }

    blit_flush_triangle_fan();
    blit_fbo_unbind();
}
