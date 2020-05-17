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
#include "my_gl.h"

void Thing::blit_non_player_owned_shadow (const Tpp &tpp, const Tilep &tile,
                                          const spoint &blit_tl,
                                          const spoint &blit_br)
{_
    spoint shadow_bl(blit_tl.x, blit_br.y);
    spoint shadow_br(blit_br.x, blit_br.y);
    spoint shadow_tl = shadow_bl;
    spoint shadow_tr = shadow_br;

    float dx = 1.0;
    float dy = 1.0;
    if (level->player) {
        if (get_owner_id() == level->player->id) {
            // use default shadow for carried items
        } else if (this != level->player) {
            fpoint p = level->player->get_interpolated_mid_at();
            fpoint d = get_interpolated_mid_at() -
                             level->player->get_interpolated_mid_at();
            const float D = 16.0;
            dx = d.x / D;
            dy = d.y / D;

            if (distance(mid_at, p) > TILES_ACROSS / 2) {
                return;
            }
        }
    } else {
        // use default shadow
    }

    float n = 0.0;
    if (dy < 0) {
        dy = std::min(-n, dy);
    } else {
        dy = std::max(n, dy);
    }

    //
    // Max length of shadow
    //
    float m = 3;
    if (dx < 0) {
        dx = std::max(-m, dx);
    } else {
        dx = std::min(m, dx);
    }
    if (dy < 0) {
        dy = std::max(-m, dy);
    } else {
        dy = std::min(m, dy);
    }

    shadow_tl.x += (float)TILE_WIDTH * dx * 10;
    shadow_tr.x += (float)TILE_WIDTH * dx * 10;
    shadow_tl.y += (float)TILE_WIDTH * dy * 10;
    shadow_tr.y += (float)TILE_WIDTH * dy * 10;

    if (shadow_tl.x > shadow_tr.x) {
        std::swap(shadow_tl, shadow_tr);
    }

    float height = get_bounce() / 2.0;
    float fadeup = get_fadeup();
    if (fadeup < 0) {
        return;
    }
    height += fadeup;

    shadow_tl.x -= height;
    shadow_tr.x -= height;
    shadow_bl.x -= height;
    shadow_br.x -= height;
    shadow_tl.y -= height;
    shadow_tr.y -= height;
    shadow_bl.y -= height;
    shadow_br.y -= height;

    color c = BLACK;
    c.a = 150;
    glcolor(c);
    tile_blit(tile, shadow_bl, shadow_br, shadow_tl, shadow_tr);
    glcolor(WHITE);
}

void Thing::blit_player_owned_shadow (const Tpp &tpp, const Tilep &tile,
                                      const spoint &blit_tl,
                                      const spoint &blit_br)
{_
    spoint shadow_tl = blit_tl;
    spoint shadow_br = blit_br;

    float dx = game->config.one_pixel_width;
    float dy = game->config.one_pixel_width;

    color c = BLACK;
    c.a = 100;

    dx *= -4;
    dy *= -4;

    glcolor(c);

    shadow_tl.x += dx;
    shadow_tl.y += dy;
    shadow_br.x += dx;
    shadow_br.y += dy;

    tile_blit(tile, shadow_tl, shadow_br);

    glcolor(WHITE);
}

void Thing::blit_shadow (const Tpp &tpp, const Tilep &tile,
                         const spoint &blit_tl, const spoint &blit_br)
{_
    if (unlikely(!game->config.gfx_lights)) {
        return;
    }

    if (!level->player) {
        blit_non_player_owned_shadow(tpp, tile, blit_tl, blit_br);
        return;
    }

    if (is_player() || (get_owner_id() == level->player->id)) {
        blit_player_owned_shadow(tpp, tile, blit_tl, blit_br);
    } else {
        blit_non_player_owned_shadow(tpp, tile, blit_tl, blit_br);
    }
}

static int blit_msg_strlen (std::string const& text)
{_
    auto text_iter = text.begin();
    int x = 0;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (c == '%') {
            if (text_iter != text.end()) {
                if (*text_iter == '%') {
                    text_iter++;
                }
            }

            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "bg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2color(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tp(tmp, &len);
                text_iter += len + 1;

                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                (void) string2tile(tmp, &len);
                text_iter += len + 1;
                continue;
            }
        }

        x++;
    }

    return (x);
}

void Thing::blit_text (std::string const& text,
                       spoint& blit_tl, spoint& blit_br)
{_
    Tilep tile;
    auto text_iter = text.begin();
    color fg = WHITE;
    fg.a = alpha;

    tile = nullptr;

    int l = blit_msg_strlen(text);

    blit_tl.x = ((blit_br.x + blit_tl.x) / 2) - (FONT_SIZE * l / 2);;
    blit_br.x = blit_tl.x + FONT_SIZE - 1;
    blit_tl.y = ((blit_br.y + blit_tl.y) / 2) - (FONT_SIZE * l / 2);;
    blit_br.y = blit_tl.y + FONT_SIZE - 1;

    while (text_iter != text.end()) {
        auto c = *text_iter;
        text_iter++;

        if (unlikely(c == L'%')) {
            if (std::string(text_iter, text_iter + 3) == "fg=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());
                int len = 0;
                fg = string2color(tmp, &len);
                fg.a = alpha;
                text_iter += len + 1;
                continue;
            } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                text_iter += 3;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                auto tp = string2tp(tmp, &len);
                text_iter += len;

                tile = tp_first_tile(tp);
                continue;
            } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                text_iter += 4;
                continue;
            } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                text_iter += 5;
                auto tmp = std::string(text_iter, text.end());

                int len = 0;
                tile = string2tile(tmp, &len);
                text_iter += len;
                continue;
            }
            continue;
        }

        tile = fixed_font->unicode_to_tile(c);

        tile_blit_outline(tile, blit_tl, blit_br, fg);

        tile = nullptr;
        blit_tl.x += FONT_SIZE;
        blit_br.x += FONT_SIZE;
    }
}

bool Thing::get_coords (spoint &blit_tl,
                        spoint &blit_br,
                        spoint &pre_effect_blit_tl,
                        spoint &pre_effect_blit_br,
                        Tilep &tile,
                        bool reflection)
{_
    fpoint mid_at = get_interpolated_mid_at();
    int x = (int)mid_at.x;
    int y = (int)mid_at.y;

    //
    // We render these offset form their owner, so if dead, then it is
    // likely they also have no owner as the swing has ended.
    //
    auto tpp = tp();
    auto blit = true;

    if (unlikely(is_hidden)) {
        blit = false;
    } else if (unlikely(tp_gfx_is_attack_anim(tpp) ||
                        tp_gfx_is_weapon_carry_anim(tpp))) {
        //
        // Hide weapons that have swung
        //
        if (is_dead) {
            blit = false;
        }
    } else if (unlikely(is_cursor() || is_cursor_path())) {
        //
        // Blit only if we need the cursor
        //
        blit = true;
    } else if (unlikely(game->config.gfx_show_hidden)) {
        if (level->is_visited(x, y)) {
            if (is_wall()) {
                glcolor(RED);
            }
        } else {
            if (is_wall()) {
                glcolor(BLUE);
            }
        }
    }

    //
    // Keep track of what we are submerged in!
    //
    is_in_lava = false;
    is_in_water = false;

    float tilew = game->config.tile_pix_width;
    float tileh = game->config.tile_pix_height;
    float X = mid_at.x;
    float Y = mid_at.y;

    blit_tl.x = (float)X * tilew;
    blit_tl.y = (float)Y * tileh;
    blit_br.x = blit_tl.x + tilew;
    blit_br.y = blit_tl.y + tileh;

    //
    // Some things (like messages) have no tiles and so use the default.
    //
    float tile_pix_width = TILE_WIDTH;
    float tile_pix_height = TILE_HEIGHT;
    if (!is_no_tile()) {
        tile = tile_index_to_tile(tile_curr);
        if (!tile) {
            err("has no tile, index %d", tile_curr);
            blit = false;
        }
        tile_pix_width = tile->pix_width;
        tile_pix_height = tile->pix_height;
    } else {
        tile = {};
    }

    //
    // Scale up tiles that are larger to the same pix scale.
    //
    if (unlikely((tile_pix_width != TILE_WIDTH) ||
                 (tile_pix_height != TILE_HEIGHT))) {
        auto xtiles = tile_pix_width / TILE_WIDTH;
        blit_tl.x -= ((xtiles-1) * tilew) / 2;
        blit_br.x += ((xtiles-1) * tilew) / 2;

        auto ytiles = tile_pix_height / TILE_HEIGHT;
        blit_tl.y -= ((ytiles-1) * tileh) / 2;
        blit_br.y += ((ytiles-1) * tileh) / 2;
    }

    //
    // Put larger tiles on the same y base as small ones.
    //
    if (unlikely(tp_gfx_oversized_but_sitting_on_the_ground(tpp))) {
        float y_offset =
            (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) * tileh) / 2.0;
        blit_tl.y -= y_offset;
        blit_br.y -= y_offset;
    }

    //
    // Flipping
    //
    if (unlikely(tp_gfx_animated_can_hflip(tpp))) {
        if (get_timestamp_flip_start()) {
            //
            // Slow flip
            //
            auto diff = time_get_time_ms_cached() - get_timestamp_flip_start();
            timestamp_t flip_time = 100;
            timestamp_t flip_steps = flip_time;

            if (diff > flip_time) {
                set_timestamp_flip_start(0);
                is_facing_left = !is_facing_left;
                if (is_dir_left() ||
                    is_dir_tl()   ||
                    is_dir_bl()) {
                    std::swap(blit_tl.x, blit_br.x);
                }
            } else {
                if (is_dir_right() ||
                    is_dir_tr()   ||
                    is_dir_br()) {
                    std::swap(blit_tl.x, blit_br.x);
                }
                float w = blit_br.x - blit_tl.x;
                float dw = w / flip_steps;
                float tlx = blit_tl.x;
                float brx = blit_br.x;

                blit_tl.x = tlx + dw * diff;
                blit_br.x = brx - dw * diff;
                std::swap(blit_tl.x, blit_br.x);
            }
        } else {
            //
            // Fast flip
            //
            if (is_dir_right() || is_dir_tr() || is_dir_br()) {
                std::swap(blit_tl.x, blit_br.x);
            }
        }
    }

    if (unlikely(tp_gfx_animated_can_vflip(tpp))) {
        if (is_dir_down() || is_dir_br() || is_dir_bl()) {
            std::swap(blit_tl.y, blit_br.y);
        }
    }

    pre_effect_blit_tl = blit_tl;
    pre_effect_blit_br = blit_br;

    auto owner = owner_get();

    //
    // Boing.
    //
    if (unlikely(is_bouncing)) {
        float b = get_bounce();
        blit_tl.y -= (tileh / TILE_HEIGHT) * (int)(b * TILE_HEIGHT);
        blit_br.y -= (tileh / TILE_HEIGHT) * (int)(b * TILE_HEIGHT);
    }

    //
    // Lunge to attack.
    //
    float lunge;
    if (owner) {
        lunge = owner->get_lunge();
    } else {
        lunge = get_lunge();
    }
    if (unlikely(lunge > 0.0)) {
        fpoint delta;
        if (owner) {
            delta = owner->get_lunge_to() - owner->get_interpolated_mid_at();
        } else {
            delta = get_lunge_to() - get_interpolated_mid_at();
        }
        float dx = -delta.x * lunge;
        float dy = -delta.y * lunge;
        dx = -delta.x * lunge * TILE_WIDTH;
        dy = delta.y * lunge * TILE_HEIGHT;
        blit_tl.x -= dx;
        blit_br.x -= dx;
        blit_tl.y += dy;
        blit_br.y += dy;
    }

    //
    // Fading.
    //
    float fadeup = get_fadeup();
    if (likely(fadeup == 0)) {
    } else if (fadeup < 0) {
        blit = false;
    } else {
        if (reflection) {
            blit_tl.y += fadeup;
            blit_br.y += fadeup;
        } else {
            blit_tl.y -= fadeup;
            blit_br.y -= fadeup;
        }
    }

    //
    // If the owner is submerged, so is the weapon
    //
    if (owner && owner->is_in_water) {
        is_in_water = true;
    }

    if (unlikely(is_monst() ||
                 is_player() ||
                 tp_gfx_is_attack_anim(tpp) ||
                 tp_gfx_is_on_fire_anim(tpp) ||
                 tp_gfx_is_weapon_carry_anim(tpp))) {
        //
        // Render the weapon and player on the same tile rules
        //
        auto map_loc = mid_at;
        if (owner) {
            map_loc = owner->mid_at;
        }

        set_submerged_offset(0);

        if (level->is_deep_water((int)map_loc.x, (int)map_loc.y)) {
            is_in_water = true;
            set_submerged_offset(8);
        } else if (level->is_lava((int)map_loc.x, (int)map_loc.y)) {
            is_in_lava = true;
            set_submerged_offset(TILE_HEIGHT / 2);
        } else if (level->is_water((int)map_loc.x, (int)map_loc.y)) {
            set_submerged_offset(4);
            is_in_water = true;
        }
    }

    return (blit);
}

bool Thing::get_map_offset_coords (spoint &blit_tl, spoint &blit_br,
                                   Tilep &tile, bool reflection)
{_
    spoint pre_effect_blit_tl;
    spoint pre_effect_blit_br;

    auto blit = get_coords(blit_tl, blit_br,
                           pre_effect_blit_tl,
                           pre_effect_blit_br,
                           tile, reflection);

    float dx = - level->pixel_map_at.x;
    float dy = - level->pixel_map_at.y;
    blit_tl.x += dx;
    blit_tl.y += dy;
    blit_br.x += dx;
    blit_br.y += dy;

    if (!reflection) {
        last_blit_tl = blit_tl;
        last_blit_br = blit_br;
    }

    return (blit);
}

bool Thing::get_pre_effect_map_offset_coords (spoint &blit_tl,
                                              spoint &blit_br,
                                              Tilep &tile,
                                              bool reflection)
{_
    spoint pre_effect_blit_tl;
    spoint pre_effect_blit_br;

    auto blit = get_coords(blit_tl, blit_br,
                           pre_effect_blit_tl,
                           pre_effect_blit_br,
                           tile,
                           false);

    float dx = - level->pixel_map_at.x;
    float dy = - level->pixel_map_at.y;
    pre_effect_blit_tl.x += dx;
    pre_effect_blit_tl.y += dy;
    pre_effect_blit_br.x += dx;
    pre_effect_blit_br.y += dy;

    blit_tl = pre_effect_blit_tl;
    blit_br = pre_effect_blit_br;

    return (blit);
}

uint8_t Thing::blit_begin_submerged (void)
{_
    auto submerged = get_submerged_offset();
    if (submerged) {
        blit_flush();
        auto waterline = last_blit_br.y;
        auto owner = owner_get();
        if (owner) {
            waterline = owner->last_blit_br.y;
        }
        glScissor(0, game->config.inner_pix_height - waterline,
                  game->config.inner_pix_width,
                  game->config.inner_pix_height);
        glEnable(GL_SCISSOR_TEST);
        glTranslatef(0, submerged, 0);
        blit_init();
    }
    return (submerged);
}

void Thing::blit_end_submerged (uint8_t submerged)
{_
    blit_flush();
    glTranslatef(0, -submerged, 0);
    glDisable(GL_SCISSOR_TEST);

    blit_init();
}

uint8_t Thing::blit_begin_reflection_submerged (void)
{_
    auto submerged = get_submerged_offset();
    if (submerged) {
        blit_flush();
        auto waterline = last_blit_br.y;
        auto owner = owner_get();
        if (owner) {
            waterline = owner->last_blit_br.y;
        }
        glTranslatef(0, -submerged, 0);
        blit_init();
    }
    return (submerged);
}

void Thing::blit_end_reflection_submerged (uint8_t submerged)
{_
    blit_flush();
    glTranslatef(0, submerged, 0);
    blit_init();
}

void Thing::blit_internal (spoint &blit_tl,
                           spoint &blit_br,
                           const Tilep tile,
                           color c,
                           bool reflection)
{_
    auto tpp = tp();

    if (unlikely(tp_gfx_small_shadow_caster(tpp))) {
        if (auto submerged = blit_begin_submerged()) {
            blit_shadow(tpp, tile, blit_tl, blit_br);
            blit_end_submerged(submerged);
        } else {
            blit_shadow(tpp, tile, blit_tl, blit_br);
        }
    }

    if (unlikely(is_msg())) {
        blit_text(get_msg(), blit_tl, blit_br);
    }

    if (unlikely(get_on_fire_anim_id())) {
        static uint32_t ts;
        if (time_have_x_tenths_passed_since(1, ts)) {
            ts = time_get_time_ms_cached();
            if (random_range(0, 100) < 10) {
                c = WHITE;
            } else if (random_range(0, 100) < 50) {
                c = ORANGE;
            } else {
                c = RED;
            }
        }
    }

    { // if (!is_wall() && !is_rock()) {
        uint8_t fade = level->is_fade_in_unsafe(mid_at.x, mid_at.y);
        if (fade) {
            level->incr_fade_in_unsafe(mid_at.x, mid_at.y);
            c.a = fade;
        } else {
            c.a = 0;
        }
    }

    glcolor(c);

    if (tp_gfx_show_outlined(tpp) && !g_render_black_and_white) {
        if (reflection) {
            if (auto submerged = blit_begin_reflection_submerged()) {
                tile_blit(tile, blit_tl, blit_br);
                blit_end_reflection_submerged(submerged);
            } else {
                tile_blit(tile, blit_tl, blit_br);
            }
        } else if (auto submerged = blit_begin_submerged()) {
            tile_blit_outline(tile, blit_tl, blit_br, c);
            blit_end_submerged(submerged);
        } else {
            tile_blit_outline(tile, blit_tl, blit_br, c);
        }
    } else {
        tile_blit(tile, blit_tl, blit_br);
    }

    get_tiles();
    if (is_wall()) {
        if (!reflection) {
            blit_wall_shadow(blit_tl, blit_br, &tiles);
        }
        blit_wall_cladding(blit_tl, blit_br, &tiles);
    }

    glcolor(WHITE);

    is_blitted = true;
}

void Thing::blit (void)
{_
    spoint blit_tl, blit_br;
    Tilep tile = {};

    if (!get_map_offset_coords(blit_tl, blit_br, tile, false)) {
        return;
    }

    blit_internal(blit_tl, blit_br, tile, WHITE, false);
}

void Thing::blit_upside_down (void)
{_
    spoint blit_tl, blit_br;
    Tilep tile = {};
    auto tpp = tp();

    if (!get_map_offset_coords(blit_tl, blit_br, tile, true)) {
        return;
    }

    auto diff = blit_br.y - blit_tl.y;
    std::swap(blit_tl.y, blit_br.y);

    if (tile && tile_get_height(tile) != TILE_HEIGHT) {
        if (tp_gfx_oversized_but_sitting_on_the_ground(tpp)) {
            blit_br.y += diff;
            blit_tl.y += diff;
        } else {
            blit_br.y += TILE_HEIGHT;
            blit_tl.y += TILE_HEIGHT;
        }
    } else {
        blit_br.y += diff;
        blit_tl.y += diff;
    }

    color reflection = {0,155,155,100};
    glcolor(reflection);
    blit_internal(blit_tl, blit_br, tile, reflection, true);
}
