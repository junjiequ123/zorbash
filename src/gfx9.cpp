//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_tile.h"
#include "my_gfx.h"

void gfx_init9 (void)
{
  std::initializer_list<std::string> tiles = {
    "ui9,0,0", "ui9,1,0", "ui9,2,0", "ui9,3,0", "ui9,4,0", "ui9,5,0", "ui9,6,0", "ui9,7,0", "ui9,8,0", "ui9,9,0", "ui9,10,0", "ui9,11,0", "ui9,12,0", "ui9,13,0", "ui9,14,0", "ui9,15,0",
    "ui9,0,1", "ui9,1,1", "ui9,2,1", "ui9,3,1", "ui9,4,1", "ui9,5,1", "ui9,6,1", "ui9,7,1", "ui9,8,1", "ui9,9,1", "ui9,10,1", "ui9,11,1", "ui9,12,1", "ui9,13,1", "ui9,14,1", "ui9,15,1",
    "ui9,0,2", "ui9,1,2", "ui9,2,2", "ui9,3,2", "ui9,4,2", "ui9,5,2", "ui9,6,2", "ui9,7,2", "ui9,8,2", "ui9,9,2", "ui9,10,2", "ui9,11,2", "ui9,12,2", "ui9,13,2", "ui9,14,2", "ui9,15,2",
    "ui9,0,3", "ui9,1,3", "ui9,2,3", "ui9,3,3", "ui9,4,3", "ui9,5,3", "ui9,6,3", "ui9,7,3", "ui9,8,3", "ui9,9,3", "ui9,10,3", "ui9,11,3", "ui9,12,3", "ui9,13,3", "ui9,14,3", "ui9,15,3",
    "ui9,0,4", "ui9,1,4", "ui9,2,4", "ui9,3,4", "ui9,4,4", "ui9,5,4", "ui9,6,4", "ui9,7,4", "ui9,8,4", "ui9,9,4", "ui9,10,4", "ui9,11,4", "ui9,12,4", "ui9,13,4", "ui9,14,4", "ui9,15,4",
    "ui9,0,5", "ui9,1,5", "ui9,2,5", "ui9,3,5", "ui9,4,5", "ui9,5,5", "ui9,6,5", "ui9,7,5", "ui9,8,5", "ui9,9,5", "ui9,10,5", "ui9,11,5", "ui9,12,5", "ui9,13,5", "ui9,14,5", "ui9,15,5",
    "ui9,0,6", "ui9,1,6", "ui9,2,6", "ui9,3,6", "ui9,4,6", "ui9,5,6", "ui9,6,6", "ui9,7,6", "ui9,8,6", "ui9,9,6", "ui9,10,6", "ui9,11,6", "ui9,12,6", "ui9,13,6", "ui9,14,6", "ui9,15,6",
    "ui9,0,7", "ui9,1,7", "ui9,2,7", "ui9,3,7", "ui9,4,7", "ui9,5,7", "ui9,6,7", "ui9,7,7", "ui9,8,7", "ui9,9,7", "ui9,10,7", "ui9,11,7", "ui9,12,7", "ui9,13,7", "ui9,14,7", "ui9,15,7",
    "ui9,0,8", "ui9,1,8", "ui9,2,8", "ui9,3,8", "ui9,4,8", "ui9,5,8", "ui9,6,8", "ui9,7,8", "ui9,8,8", "ui9,9,8", "ui9,10,8", "ui9,11,8", "ui9,12,8", "ui9,13,8", "ui9,14,8", "ui9,15,8",
    "ui9,0,9", "ui9,1,9", "ui9,2,9", "ui9,3,9", "ui9,4,9", "ui9,5,9", "ui9,6,9", "ui9,7,9", "ui9,8,9", "ui9,9,9", "ui9,10,9", "ui9,11,9", "ui9,12,9", "ui9,13,9", "ui9,14,9", "ui9,15,9",
    "ui9,0,10", "ui9,1,10", "ui9,2,10", "ui9,3,10", "ui9,4,10", "ui9,5,10", "ui9,6,10", "ui9,7,10", "ui9,8,10", "ui9,9,10", "ui9,10,10", "ui9,11,10", "ui9,12,10", "ui9,13,10", "ui9,14,10", "ui9,15,10",
    "ui9,0,11", "ui9,1,11", "ui9,2,11", "ui9,3,11", "ui9,4,11", "ui9,5,11", "ui9,6,11", "ui9,7,11", "ui9,8,11", "ui9,9,11", "ui9,10,11", "ui9,11,11", "ui9,12,11", "ui9,13,11", "ui9,14,11", "ui9,15,11",
    "ui9,0,12", "ui9,1,12", "ui9,2,12", "ui9,3,12", "ui9,4,12", "ui9,5,12", "ui9,6,12", "ui9,7,12", "ui9,8,12", "ui9,9,12", "ui9,10,12", "ui9,11,12", "ui9,12,12", "ui9,13,12", "ui9,14,12", "ui9,15,12",
    "ui9,0,13", "ui9,1,13", "ui9,2,13", "ui9,3,13", "ui9,4,13", "ui9,5,13", "ui9,6,13", "ui9,7,13", "ui9,8,13", "ui9,9,13", "ui9,10,13", "ui9,11,13", "ui9,12,13", "ui9,13,13", "ui9,14,13", "ui9,15,13",
    "ui9,0,14", "ui9,1,14", "ui9,2,14", "ui9,3,14", "ui9,4,14", "ui9,5,14", "ui9,6,14", "ui9,7,14", "ui9,8,14", "ui9,9,14", "ui9,10,14", "ui9,11,14", "ui9,12,14", "ui9,13,14", "ui9,14,14", "ui9,15,14",
    "ui9,0,15", "ui9,1,15", "ui9,2,15", "ui9,3,15", "ui9,4,15", "ui9,5,15", "ui9,6,15", "ui9,7,15", "ui9,8,15", "ui9,9,15", "ui9,10,15", "ui9,11,15", "ui9,12,15", "ui9,13,15", "ui9,14,15", "ui9,15,15",
  };
  const std::vector<std::string> arr(tiles);
  tile_load_arr("data/gfx/ui_vert2.tga", "ui_box9", 8, 8, arr);
}
