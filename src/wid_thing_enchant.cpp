//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_game.h"
#include "my_sdl.h"
#include "my_ui.h"
#include "my_wid_popup.h"
#include "my_wid_thing_enchant.h"
#include "my_tile.h"
#include "my_wid_console.h"
#include "my_wid_thing_info.h"
#include "my_wid_bag.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_monst.h"

static WidPopup *wid_enchant;
static std::vector<Thingp> enchant_items;

static void wid_enchant_destroy (void)
{_
    delete wid_enchant;
    wid_enchant = nullptr;
    game->hard_unpause();
}

static uint8_t wid_enchant_key_up (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9': {
                        int slot = c - '0';
                        TOPCON("TODO %d",slot);
                        return true;
                    }
                    case 'b':
                    case SDLK_ESCAPE: {_
                        CON("PLAYER: Load game cancelled");
                        wid_enchant_destroy();
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

static uint8_t wid_enchant_key_down (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

static uint8_t wid_enchant_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    auto slot = wid_get_int_context(w);
    TOPCON("slot %d",slot);
    return true;
}

void Game::wid_thing_enchant_create (void)
{_
    LOG("Thing enchant create");

    auto player = game->level->player;
    if (!player){
        ERR("No player");
        return;
    }

    std::map<Tpp, bool> found;
    for (auto id : player->monstp->carrying) {
        auto t = thing_find(id);
        if (t) {
            auto tp = t->tp();
            if (found.find(tp) != found.end()) {
                continue;
            }
            if (t->is_enchantable()) {
                found[tp] = true;
                enchant_items.push_back(t);
                enchant_items.push_back(t);
                enchant_items.push_back(t);
                enchant_items.push_back(t);
                enchant_items.push_back(t);
                enchant_items.push_back(t);
                enchant_items.push_back(t);
                enchant_items.push_back(t);
            }
        }
    }

    for (auto id : player->monstp->skills) {
        auto t = thing_find(id);
        if (t) {
            auto tp = t->tp();
            if (found.find(tp) != found.end()) {
                continue;
            }
            if (t->is_enchantable()) {
                found[tp] = true;
                enchant_items.push_back(t);
            }
        }
    }

    auto m = TERM_WIDTH / 2;
    point tl = make_point(m - 30, UI_TOPCON_VIS_HEIGHT + 10);
    point br = make_point(m + 30, tl.y + 25);
    auto width = br.x - tl.x;

    wid_enchant = new WidPopup("Enchant", tl, br, nullptr, "", false, true);
    wid_set_on_key_up(wid_enchant->wid_popup_container, wid_enchant_key_up);
    wid_set_on_key_down(wid_enchant->wid_popup_container, wid_enchant_key_down);

    wid_enchant->log("Choose something to enchant");

    int y_at = 3;
    for (auto slot = 0; slot < (int)enchant_items.size(); slot++) {
        Game tmp;
        auto p = wid_enchant->wid_text_area->wid_text_area;
        auto w = wid_new_container(p, "item slot");
        point tl = make_point(0, y_at);
        point br = make_point(width - 3, y_at + 2);
        wid_set_pos(w, tl, br);
        wid_set_shape_none(w);
        //wid_set_style(w, UI_WID_STYLE_DARK);
        //wid_set_text(w, "xxxxxxxxx");
        //wid_set_on_mouse_up(w, wid_enchant_mouse_up);

        auto t = enchant_items[slot];

        {
            auto icon = wid_new_square_button(w, "item slot");
            point tl = make_point(0, 0);
            point br = make_point(2, 2);
            wid_set_pos(icon, tl, br);

            auto tpp = t->tp();
            auto tiles = &tpp->tiles;
            if (tiles) {
                auto tile = tile_first(tiles);
                if (tile) {
                    wid_set_style(icon, UI_WID_STYLE_DARK);
                    wid_set_fg_tile(icon, tile);
                }
            }
        }

        {
            auto wid_item = wid_new_square_button(w, "item slot");
            point tl = make_point(3, 0);
            point br = make_point(width - 2, 2);
            wid_set_pos(wid_item, tl, br);
            wid_set_style(wid_item, UI_WID_STYLE_DARK);
            wid_set_int_context(w, slot);
            wid_set_text(wid_item, " " + t->text_name() + ", " + t->text_enchant());
            wid_set_text_lhs(wid_item, true);
            wid_set_on_mouse_up(wid_item, wid_enchant_mouse_up);
        }

        y_at += 3;
    }

    wid_update(wid_enchant->wid_text_area->wid_text_area);
}
