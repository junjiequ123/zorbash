//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_debuffbox.hpp"
#include "my_wid_thing_info.hpp"

bool Thing::debuffbox_id_insert(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("debuffbox insert %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  if (! maybe_itemp()) {
    return false;
  }

  int  free_slot       = -1;
  auto debuffbox_items = player->get_itemp()->debuffbox_id.size();
  for (auto i = 0U; i < debuffbox_items; i++) {
    auto thing_id = get_itemp()->debuffbox_id[ i ];
    if (! thing_id) {
      if (free_slot == -1) {
        free_slot = i;
      }
      continue;
    }

    auto t = level->thing_find(thing_id);
    if (! t) {
      continue;
    }

    if (what == t) {
      if (what->is_bag_item_not_stackable()) {
        //
        // Needs its own slot
        //
      } else {
        wid_debuffbox_init();
        if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
            (game->state != Game::STATE_COLLECTING_ITEMS)) {
          wid_thing_info_fini();
        }
        return true;
      }
    }
  }

  int item_slot = -1;
  if (free_slot != -1) {
    get_itemp()->debuffbox_id[ free_slot ] = what->id;
    item_slot                              = free_slot;
  } else {
    if (debuffbox_items >= UI_INVENTORY_QUICK_ITEMS_MAX) {
      TOPCON("No space to carry %s which is not carried.", what->text_the().c_str());
      return false;
    }

    get_itemp()->debuffbox_id.push_back(what->id);
    item_slot = get_itemp()->debuffbox_id.size() - 1;
  }

  game->previous_slot = item_slot;

  wid_debuffbox_init();
  if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
      (game->state != Game::STATE_COLLECTING_ITEMS)) {
    wid_thing_info_fini();
  }
  level->debuffbox_describe(item_slot);
  return true;
}

bool Thing::debuffbox_id_remove(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("debuffbox remove %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto player = level->player;
  if (! player) {
    return false;
  }

  if (! is_player()) {
    return false;
  }

  if (! maybe_itemp()) {
    return false;
  }

  auto immediate_owner = what->get_immediate_owner();
  if (immediate_owner) {
    immediate_owner->bag_remove(what);
  }

  auto debuffbox_items = player->get_itemp()->debuffbox_id.size();
  for (auto i = 0U; i < debuffbox_items; i++) {
    auto thing_id = get_itemp()->debuffbox_id[ i ];
    if (! thing_id) {
      continue;
    }
    auto t = level->thing_find(thing_id);
    if (! t) {
      continue;
    }

    if (what == t) {
      game->request_remake_debuffbox = true;

      dbg("Remove slot");
      get_itemp()->debuffbox_id[ i ] = NoThingId;

      wid_debuffbox_init();
      if ((game->state != Game::STATE_CHOOSING_TARGET) && (game->state != Game::STATE_INVENTORY) &&
          (game->state != Game::STATE_COLLECTING_ITEMS)) {
        wid_thing_info_fini();
      }
      return true;
    }
  }
  return false;
}

Thingp Level::debuffbox_get(const uint32_t slot)
{
  TRACE_AND_INDENT();
  dbg("debuffbox get slot %d", slot);
  TRACE_AND_INDENT();
  if (! player) {
    ERR("No player");
    return nullptr;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return nullptr;
  }

  if (slot >= itemp->debuffbox_id.size()) {
    LOG("Slot %d out of range, max %d", slot, (int) itemp->debuffbox_id.size());
    return nullptr;
  }

  auto thing_id = get(itemp->debuffbox_id, slot);
  if (! thing_id) {
    LOG("Slot %d has no tp", slot);
    return nullptr;
  }

  auto t = thing_find(thing_id);
  if (! t) {
    LOG("Slot %d has no valid tp", slot);
    return nullptr;
  }

  LOG("Slot %d has %s", slot, t->name().c_str());

  for (auto oid : itemp->debuffs) {
    auto o = thing_find(oid);
    if (o) {
      if (o == t) {
        IF_DEBUG2 { o->log("Got debuffbox item %s", t->name().c_str()); }
        return o;
      }
    }
  }

  LOG("Slot %d has debuff tp %s that is not carried", slot, t->name().c_str());
  return nullptr;
}

bool Level::debuffbox_over(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("debuffbox: Over debuffbox slot %d", slot);
  TRACE_AND_INDENT();
  if (! player) {
    LOG("debuffbox: Ignore; no player");
    return false;
  }

  auto itemp = player->maybe_itemp();
  if (! itemp) {
    ERR("No itemp for player");
    return false;
  }

  if (slot >= itemp->debuffbox_id.size()) {
    LOG("debuffbox: Ignore; slot out of range");
    return false;
  }

  auto oid = get(itemp->debuffbox_id, slot);
  if (! oid) {
    LOG("debuffbox: Ignore; nothing at that slot");
    return false;
  }

  Thingp what;

  what = debuffbox_describe(slot);
  if (! what) {
    return false;
  }

  IF_DEBUG2 { what->log("Over debuffbox item"); }
  return true;
}

Thingp Level::debuffbox_describe(const uint32_t slot)
{
  TRACE_AND_INDENT();
  LOG("debuffbox: Describe slot %d", slot);
  TRACE_AND_INDENT();
  auto what = debuffbox_get(slot);
  if (what) {
    IF_DEBUG2 { what->log("debuffbox: Describe slot %d", slot); }
    what->describe_when_hovered_over_in_rightbar();
  } else {
    LOG("debuffbox: Describe slot %d => nothing there", slot);
  }
  return what;
}
