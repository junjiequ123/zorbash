//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_inventory.h"
#include "my_wid_thing_info.h"
#include "my_wid_actionbar.h"
#include "my_sys.h"
#include "my_game.h"
#include "my_thing.h"
#include "my_wid_bag.h"

void Game::change_state (int new_state)
{
  if (wid_over) {
    if (game->level) {
      game->level->cursor_path_clear();
    }
  }

  if (game->state == new_state) {
    return;
  }
_
  auto old_state = state;

  //
  // Set here to stop recursion.
  //
  state = new_state;

  switch (new_state) {
    case STATE_NORMAL:
      LOG("State changing to STATE_NORMAL");
      wid_thing_info_fini();
      wid_collect_destroy();
      wid_wield_destroy();
      wid_enchant_destroy();
      wid_skill_choose_destroy();
      wid_item_options_destroy();
      wid_load_destroy();
      wid_save_destroy();
      game_quit_destroy();
      LOG("State changed to STATE_NORMAL");
      break;
    case STATE_OPTIONS_FOR_ITEM_MENU:
      LOG("State changed to STATE_OPTIONS_FOR_ITEM_MENU");
      break;
    case STATE_MOVING_ITEMS:     // Currently managing inventory
      LOG("State changed to STATE_MOVING_ITEMS");
      break;
    case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
      LOG("State changing to STATE_COLLECTING_ITEMS");
      wid_thing_info_fini();
      wid_collect_destroy();
      LOG("State changed to STATE_COLLECTING_ITEMS");
      break;
    case STATE_WIELDING_ITEMS:
      LOG("State changing to STATE_WIELDING_ITEMS");
      wid_thing_info_fini();
      wid_wield_destroy();
      LOG("State changed to STATE_WIELDING_ITEMS");
      break;
    case STATE_ENCHANTING_ITEMS:
      LOG("State changing to STATE_ENCHANTING_ITEMS");
      wid_enchant_destroy();
      LOG("State changed to STATE_ENCHANTING_ITEMS");
      break;
    case STATE_CHOOSING_SKILLS:
      LOG("State changing to STATE_CHOOSING_SKILLS");
      wid_skill_choose_destroy();
      LOG("State changed to STATE_CHOOSING_SKILLS");
      break;
    case STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
      LOG("State changing to STATE_CHOOSING_TARGET");
      wid_thing_info_fini();
      LOG("State changed to STATE_CHOOSING_TARGET");
      break;
    case STATE_LOAD_MENU:
    case STATE_SAVE_MENU:
    case STATE_QUIT_MENU:
      wid_thing_info_fini();
      break;
  }

  //
  // In case some cleanup above changed state
  //
  state = new_state;
  wid_actionbar_init();

  if (game->in_transit_item) {
    if (wid_in_transit_item_drop()) {
      game->tick_begin("drop in transit item");
    }
    wid_destroy(&game->in_transit_item);
  }

  request_to_throw_item = nullptr;
  request_to_fire_item = nullptr;

  switch (old_state) {
    case STATE_NORMAL:
    case STATE_MOVING_ITEMS:     // Currently managing inventory
    case STATE_COLLECTING_ITEMS: // Collecting en masse from the level
    case STATE_WIELDING_ITEMS:
    case STATE_ENCHANTING_ITEMS:
    case STATE_CHOOSING_SKILLS:
      if (level) {
        level->cursor_recreate();
        if (level->cursor) {
          level->cursor->clear_move_path("State change");
        }
      }
      break;
    case STATE_CHOOSING_TARGET:  // Looking to somewhere to throw at
      //
      // Don't create the cursor right after selecting. Wait until
      // we move again.
      //
      if (level) {
        level->cursor_recreate();
        level->cursor_path_clear();
      }
      break;
  }

  wid_inventory_init();
}
