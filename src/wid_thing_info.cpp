//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_botcon.h"
#include "my_wid_popup.h"
#include "my_wid_thing_info.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_wid_console.h"
#include "my_wid_bag.h"
#include "my_traceback.h"

WidPopup *wid_thing_info_window;

void wid_thing_info_fini (void)
{_
    if (game->bag_primary) {
        delete game->bag_primary;
        game->bag_primary = nullptr;
    }

    if (game->bag_secondary) {
        delete game->bag_secondary;
        game->bag_secondary = nullptr;
    }

    delete wid_thing_info_window;
    wid_thing_info_window = nullptr;
}

uint8_t wid_thing_info_init (void)
{_
    return true;
}

void Game::wid_thing_info_destroy (void)
{_
    if (game->request_remake_inventory) {
        //
        // Continue
        //
    } else if (game->state == Game::STATE_MOVING_ITEMS) {
        return;
    }

    wid_thing_info_fini();
}

void Game::wid_thing_info_create (Thingp t, bool when_hovering_over)
{_
    if (game->request_remake_inventory) {
        //
        // Continue
        //
        t->log("Remake thing info");
    } else if (game->state == Game::STATE_MOVING_ITEMS) {
        t->log("Ignore, already moving items");
        return;
    }

    if (wid_console_window && wid_console_window->visible) {
        t->log("Console visible");
        return;
    }

    if (wid_thing_info_window) {
        t->log("Destroy window");
        wid_thing_info_destroy();
    }

    auto player = game->level->player;
    if (!player){
        game->change_state(Game::STATE_NORMAL);
        ERR("No player");
        return;
    }

    int height = 33;
    point tl = make_point(0, TERM_HEIGHT - 2 - height);
    point br = make_point(20, TERM_HEIGHT - 2);

    auto tp = t->tp();
    auto tiles = &tp->tiles;
    auto tile = tile_first(tiles);
    if (!tile) {
        t->log("No tile for thing info");
        game->change_state(Game::STATE_NORMAL);
        return;
    }

    static bool recursion;
    if (recursion) {
        DIE("Recursion");
    }
    recursion = true;

    t->log("Thing info create window");

    wid_thing_info_window = new WidPopup("Thing info", tl, br, nullptr, "", true, false);
    wid_raise(wid_thing_info_window->wid_popup_container);

    {_
        auto w = wid_new_plain(wid_thing_info_window->wid_popup_container, "ui-circle");
        point tl = make_point(8, 1);
        point br = make_point(12, 4);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_circle");
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, UI_WID_STYLE_NONE);
    }

    {_
        auto w = wid_new_plain(wid_thing_info_window->wid_popup_container, "ui-circle");
        point tl = make_point(9, 2);
        point br = make_point(11, 3);
        wid_set_ignore_events(w, true);
        wid_set_pos(w, tl, br);
        wid_set_bg_tilename(w, "ui_tile_bg");
        wid_set_fg_tilename(w, tile->name);
        wid_set_color(w, WID_COLOR_BG, WHITE);
        wid_set_style(w, UI_WID_STYLE_NONE);
    }

    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(" ");
    wid_thing_info_window->log(tp->long_text_description());

    if (t->is_item()) {
        if (tp->rarity() == THING_RARITY_UNCOMMON) {
            wid_thing_info_window->log("Uncommon item");
        } else if (tp->rarity() == THING_RARITY_RARE) {
            wid_thing_info_window->log("Rare item");
        } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
            wid_thing_info_window->log("Very rare item");
        } else if (tp->rarity() == THING_RARITY_UNIQUE) {
            wid_thing_info_window->log("Unique item");
        }
    }

    if (t->is_monst()) {
        if (tp->rarity() == THING_RARITY_UNCOMMON) {
            wid_thing_info_window->log("Uncommon monster");
        } else if (tp->rarity() == THING_RARITY_RARE) {
            wid_thing_info_window->log("Rare monster");
        } else if (tp->rarity() == THING_RARITY_VERY_RARE) {
            wid_thing_info_window->log("Very rare monster");
        } else if (tp->rarity() == THING_RARITY_UNIQUE) {
            wid_thing_info_window->log("Unique monster");
        }
    }

    bool need_line = true;

    {
        auto attack_dice = t->get_stats_attack_dice();
        auto min_value = attack_dice.min_roll();
        auto max_value = attack_dice.max_roll();
        if (min_value > 0) {
            if (need_line) {
                wid_thing_info_window->log(" ");
                need_line = false;
            }
            if (min_value == max_value) {
                wid_thing_info_window->log("Damg: " + 
                                        t->get_stats_attack_dice_str());
            } else {
                wid_thing_info_window->log("Damg: " + 
                                        std::to_string(min_value) + "-" + 
                                        std::to_string(max_value) + " (" +
                                        t->get_stats_attack_dice_str() + ")");
            }
        }
    }

    {
        auto gold_dice = t->get_gold_value_dice();
        auto min_value = gold_dice.min_roll();
        auto max_value = gold_dice.max_roll();
        if (min_value > 0) {
            if (need_line) {
                wid_thing_info_window->log(" ");
                need_line = false;
            }
            if (min_value == max_value) {
                wid_thing_info_window->log("Gold: " + 
                                        t->get_gold_value_dice_str());
            } else {
                wid_thing_info_window->log("Gold: " + 
                                        std::to_string(min_value) + "-" + 
                                        std::to_string(max_value) + " (" +
                                        t->get_gold_value_dice_str() + ")");
            }
        }
    }

    if (player->can_eat(t)) {
        auto nutrition_dice = t->get_nutrition_dice();
        auto min_value = nutrition_dice.min_roll();
        auto max_value = nutrition_dice.max_roll();
        if (min_value > 0) {
            if (need_line) {
                wid_thing_info_window->log(" ");
                need_line = false;
            }
            if (min_value == max_value) {
                wid_thing_info_window->log("Nutn: " + 
                                        t->get_nutrition_dice_str());
            } else {
                wid_thing_info_window->log("Nutn: " + 
                                        std::to_string(min_value) + "-" + 
                                        std::to_string(max_value) + " (" + 
                                        t->get_nutrition_dice_str() + ")");
            }
        }
    }

    if (t->is_monst()) {
        std::string danger_level = player->get_danger_level(t);
        wid_thing_info_window->log(" ");
        wid_thing_info_window->log(danger_level);

        auto attack_dice = t->get_stats_attack_dice();
        auto kill_count = player->get_stats_health() / attack_dice.max_roll();

        //
        // Oh dear.
        //
        if (kill_count == 0) {
            kill_count = 1;
        }

        if (kill_count == 1) {
            wid_thing_info_window->log(" ");
            wid_thing_info_window->log("%%fg=red$Could kill you in");
            wid_thing_info_window->log("%%fg=red$" + std::to_string(kill_count) + " hit!");
        } else if (kill_count <= 2) {
            wid_thing_info_window->log(" ");
            wid_thing_info_window->log("%%fg=red$Could kill you in");
            wid_thing_info_window->log("%%fg=red$" + std::to_string(kill_count) + " hits");
        } else if (kill_count <= 5) {
            wid_thing_info_window->log(" ");
            wid_thing_info_window->log("%%fg=orange$Could kill you in");
            wid_thing_info_window->log("%%fg=orange$" + std::to_string(kill_count) + " hits");
        }
    }

    if ((t->get_top_owner() == player) || (t == player)) {
        t->log("Thing info create bags");

        point mid(TERM_WIDTH / 2, TERM_HEIGHT - 1);

        if (bag_primary) {
            delete bag_primary;
            bag_primary = nullptr;
        }

        if (bag_secondary) {
            delete bag_secondary;
            bag_secondary = nullptr;
        }

        {
            point tl = mid - point(player->bag_width() + 5, player->bag_height() + 1);
            point br = tl +  point(player->bag_width(), player->bag_height());
            bag_primary = new WidBag(player, tl, br, "Inventory");
        }

        if (t->is_bag()) {
            point tl = mid + point(0, - (t->bag_height() + 1));
            point br = tl +  point(t->bag_width(), t->bag_height());
            if (tp->bag_width() * tp->bag_height() < 100) {
                bag_secondary = new WidBag(t, tl, br, "Wee bag");
            } else {
                bag_secondary = new WidBag(t, tl, br, "Big bag");
            }
        }
    }

    int utilized = wid_thing_info_window->wid_text_area->line_count;
    wid_move_delta(wid_thing_info_window->wid_popup_container, 0, height - utilized + 2);
    wid_resize(wid_thing_info_window->wid_popup_container, -1, utilized - 2);

    wid_update(wid_thing_info_window->wid_text_area->wid_text_area);

    recursion = false;
}

void Game::wid_thing_info_create_when_hovering_over (Thingp t)
{
    wid_thing_info_create(t, true);
}
