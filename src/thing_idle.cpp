//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_wid_console.hpp"

//
// Roll the dice and see if we do anything
//
bool Thing::idle_check(void)
{
  TRACE_NO_INDENT();

  if (! std::empty(on_idle_tick_frequency_dice_str_get())) {
    auto roll = on_idle_tick_frequency_get();
    // con("%d %d roll %d", game->tick_current, tick_last_did_something_get(), roll);
    if (game->tick_current - tick_last_did_something_get() >= (unsigned int) roll) {
      // con("%d %d roll %d tick", game->tick_current, tick_last_did_something_get(), roll);
      auto d   = on_idle_tick_frequency_dice_get();
      auto mod = d.python_mod;

      if (mod == "me") {
        mod = name();
      }

      py_call_void_fn(mod.c_str(), d.python_func.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
      tick_last_did_something_set(game->tick_current);
      return true;
    }
  }
  return false;
}
