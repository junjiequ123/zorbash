//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_font.h"
#include "my_level.h"
#include "my_tex.h"
#include "my_gl.h"

void Level::display_deep_water (int fbo,
                                uint16_t minx, uint16_t miny,
                                uint16_t maxx, uint16_t maxy)
{_
#define WATER_ACROSS 8
#define WATER_DOWN   8

    static std::array<std::array<Tilep, WATER_DOWN>, WATER_ACROSS> deep_water;
    if (!deep_water[0][0]) {
        set(deep_water, 0, 0, tile_find("deep_water1a"));
        set(deep_water, 1, 0, tile_find("deep_water2a"));
        set(deep_water, 2, 0, tile_find("deep_water3a"));
        set(deep_water, 3, 0, tile_find("deep_water4a"));
        set(deep_water, 4, 0, tile_find("deep_water5a"));
        set(deep_water, 5, 0, tile_find("deep_water6a"));
        set(deep_water, 6, 0, tile_find("deep_water7a"));
        set(deep_water, 7, 0, tile_find("deep_water8a"));
        set(deep_water, 0, 1, tile_find("deep_water1b"));
        set(deep_water, 1, 1, tile_find("deep_water2b"));
        set(deep_water, 2, 1, tile_find("deep_water3b"));
        set(deep_water, 3, 1, tile_find("deep_water4b"));
        set(deep_water, 4, 1, tile_find("deep_water5b"));
        set(deep_water, 5, 1, tile_find("deep_water6b"));
        set(deep_water, 6, 1, tile_find("deep_water7b"));
        set(deep_water, 7, 1, tile_find("deep_water8b"));
        set(deep_water, 0, 2, tile_find("deep_water1c"));
        set(deep_water, 1, 2, tile_find("deep_water2c"));
        set(deep_water, 2, 2, tile_find("deep_water3c"));
        set(deep_water, 3, 2, tile_find("deep_water4c"));
        set(deep_water, 4, 2, tile_find("deep_water5c"));
        set(deep_water, 5, 2, tile_find("deep_water6c"));
        set(deep_water, 6, 2, tile_find("deep_water7c"));
        set(deep_water, 7, 2, tile_find("deep_water8c"));
        set(deep_water, 0, 3, tile_find("deep_water1d"));
        set(deep_water, 1, 3, tile_find("deep_water2d"));
        set(deep_water, 2, 3, tile_find("deep_water3d"));
        set(deep_water, 3, 3, tile_find("deep_water4d"));
        set(deep_water, 4, 3, tile_find("deep_water5d"));
        set(deep_water, 5, 3, tile_find("deep_water6d"));
        set(deep_water, 6, 3, tile_find("deep_water7d"));
        set(deep_water, 7, 3, tile_find("deep_water8d"));
        set(deep_water, 0, 4, tile_find("deep_water1e"));
        set(deep_water, 1, 4, tile_find("deep_water2e"));
        set(deep_water, 2, 4, tile_find("deep_water3e"));
        set(deep_water, 3, 4, tile_find("deep_water4e"));
        set(deep_water, 4, 4, tile_find("deep_water5e"));
        set(deep_water, 5, 4, tile_find("deep_water6e"));
        set(deep_water, 6, 4, tile_find("deep_water7e"));
        set(deep_water, 7, 4, tile_find("deep_water8e"));
        set(deep_water, 0, 5, tile_find("deep_water1f"));
        set(deep_water, 1, 5, tile_find("deep_water2f"));
        set(deep_water, 2, 5, tile_find("deep_water3f"));
        set(deep_water, 3, 5, tile_find("deep_water4f"));
        set(deep_water, 4, 5, tile_find("deep_water5f"));
        set(deep_water, 5, 5, tile_find("deep_water6f"));
        set(deep_water, 6, 5, tile_find("deep_water7f"));
        set(deep_water, 7, 5, tile_find("deep_water8f"));
        set(deep_water, 0, 6, tile_find("deep_water1g"));
        set(deep_water, 1, 6, tile_find("deep_water2g"));
        set(deep_water, 2, 6, tile_find("deep_water3g"));
        set(deep_water, 3, 6, tile_find("deep_water4g"));
        set(deep_water, 4, 6, tile_find("deep_water5g"));
        set(deep_water, 5, 6, tile_find("deep_water6g"));
        set(deep_water, 6, 6, tile_find("deep_water7g"));
        set(deep_water, 7, 6, tile_find("deep_water8g"));
        set(deep_water, 0, 7, tile_find("deep_water1h"));
        set(deep_water, 1, 7, tile_find("deep_water2h"));
        set(deep_water, 2, 7, tile_find("deep_water3h"));
        set(deep_water, 3, 7, tile_find("deep_water4h"));
        set(deep_water, 4, 7, tile_find("deep_water5h"));
        set(deep_water, 5, 7, tile_find("deep_water6h"));
        set(deep_water, 6, 7, tile_find("deep_water7h"));
        set(deep_water, 7, 7, tile_find("deep_water8h"));
    }

    auto z = MAP_DEPTH_WATER;

    /////////////////////////////////////////////////////////////////////
    // Draw white mask tiles only
    /////////////////////////////////////////////////////////////////////
    blit_init();
    glcolor(WHITE);
    glDisable(GL_TEXTURE_2D);
    blit_fbo_bind(FBO_MASK1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (likely(!level->is_deep_water(x, y))) {
                continue;
            }
            if (likely(!game->config.gfx_show_hidden)) {
                if (!is_visited(x, y)) {
                    continue;
                }
            }
            FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z) {
                auto tpp = t->tp();
                if (!tp_is_deep_water(tpp)) {
                    continue;
                }
                t->blit();
            } FOR_ALL_THINGS_END()
        }
    }
    glEnable(GL_TEXTURE_2D);
    blit_flush();

    /////////////////////////////////////////////////////////////////////
    // Draw the tiles that we will want to combine with the mask later
    /////////////////////////////////////////////////////////////////////
    blit_init();
    glcolor(WHITE);
    blit_fbo_bind(FBO_MASK2);
    glBlendFunc(GL_ONE, GL_ZERO);
    auto tile_map = level->deep_water_tile_map;
    for (auto y = miny; y < maxy; y+=2) {
        for (auto x = minx; x < maxx; x+=2) {
            if (likely(!get(tile_map, x, y))) {
                continue;
            }
            int tx = (x & ~1);
            int ty = (y & ~1);
            int tlx = tx * TILE_WIDTH;
            int tly = ty * TILE_HEIGHT;
            int brx = tlx + (2 * TILE_WIDTH);
            int bry = tly + (2 * TILE_HEIGHT);

            tlx -= pixel_map_at.x;
            tly -= pixel_map_at.y;
            brx -= pixel_map_at.x;
            bry -= pixel_map_at.y;

            auto tile = get(deep_water,
                            (x&~1) % WATER_ACROSS,
                            (y&~1) % WATER_DOWN);
                            // (y + (int)deep_water_step2/4) % WATER_DOWN);
            auto x1 = tile->x1;
            auto x2 = tile->x2;
            auto y1 = tile->y1;
            auto y2 = tile->y2;

            float one_pix = (1.0 / tex_get_height(tile->tex));
            y1 += one_pix * deep_water_step2;
            y2 += one_pix * deep_water_step2;

            blit(tile->gl_binding(), x1, y2, x2, y1, tlx, bry, brx, tly);
        }
    }
    blit_flush();

    /////////////////////////////////////////////////////////////////////
    // Merge the mask and tiles
    /////////////////////////////////////////////////////////////////////
    blit_fbo_bind(FBO_MASK3);
    glClear(GL_COLOR_BUFFER_BIT);
    blit_fbo(FBO_MASK1);
    glBlendFunc(GL_DST_ALPHA, GL_ZERO);
    blit_fbo(FBO_MASK2);

    /////////////////////////////////////////////////////////////////////
    // Merge the outline mask and the masked tiles
    /////////////////////////////////////////////////////////////////////
    glcolor(WHITE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    blit_fbo_bind(fbo);
    blit_fbo(FBO_MASK3);
}
