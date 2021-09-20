//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_game.h"
#include "my_sys.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_thing.h"
#include "my_array_bounds_check.h"

//
// Return the dmap distance. DMAP_IS_WALL if not reachable.
//
int Thing::distance_to_player (void)
{_
  auto player = game->level->player;
  if (!player) {
    return DMAP_IS_WALL;
  }

  //
  // Check we're on the same level
  //
  if (player->level != level) {
    return DMAP_IS_WALL;
  }

  return get(&game->level->dmap_to_player.val, (int)mid_at.x, (int)mid_at.y);
}

void Level::dmap_to_player_update (void)
{_
  if (!player) {
    return;
  }

#if 0
  //
  // Limit the size of the dmap for performance?
  //
  auto max_dist = 20;
  int minx = player->mid_at.x - max_dist;
  int maxx = player->mid_at.x + max_dist;
  int miny = player->mid_at.y - max_dist;
  int maxy = player->mid_at.y + max_dist;
#endif

  int minx = 0;
  int maxx = MAP_WIDTH;
  int miny = 0;
  int maxy = MAP_HEIGHT;

  //
  // Set up obstacles for the search
  //
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      if ((x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy)) {
        if (is_movement_blocking_wall_or_locked_door(point(x, y))) {
          set(dmap_to_player.val, x, y, DMAP_IS_WALL);
        } else {
          set(dmap_to_player.val, x, y, DMAP_IS_PASSABLE);
        }
      } else {
        set(dmap_to_player.val, x, y, DMAP_IS_WALL);
      }
    }
  }

  set(dmap_to_player.val, player->mid_at.x, player->mid_at.y, DMAP_IS_GOAL);

  dmap_process(&dmap_to_player);
  IF_DEBUG4 {
    LOG("Player dmap:");
    dmap_print(&dmap_to_player);
  }
}
