//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_tile.h"

void gfx_init11 (void)
{
    std::initializer_list<std::string> tiles = {
        "ui11,0,0", "ui11,1,0", "ui11,2,0", "ui11,3,0", "ui11,4,0", "ui11,5,0", "ui11,6,0", "ui11,7,0", "ui11,8,0", "ui11,9,0", "ui11,10,0", "ui11,11,0", "ui11,12,0", "ui11,13,0", "ui11,14,0", "ui11,15,0",
        "ui11,0,1", "ui11,1,1", "ui11,2,1", "ui11,3,1", "ui11,4,1", "ui11,5,1", "ui11,6,1", "ui11,7,1", "ui11,8,1", "ui11,9,1", "ui11,10,1", "ui11,11,1", "ui11,12,1", "ui11,13,1", "ui11,14,1", "ui11,15,1",
        "ui11,0,2", "ui11,1,2", "ui11,2,2", "ui11,3,2", "ui11,4,2", "ui11,5,2", "ui11,6,2", "ui11,7,2", "ui11,8,2", "ui11,9,2", "ui11,10,2", "ui11,11,2", "ui11,12,2", "ui11,13,2", "ui11,14,2", "ui11,15,2",
        "ui11,0,3", "ui11,1,3", "ui11,2,3", "ui11,3,3", "ui11,4,3", "ui11,5,3", "ui11,6,3", "ui11,7,3", "ui11,8,3", "ui11,9,3", "ui11,10,3", "ui11,11,3", "ui11,12,3", "ui11,13,3", "ui11,14,3", "ui11,15,3",
        "ui11,0,4", "ui11,1,4", "ui11,2,4", "ui11,3,4", "ui11,4,4", "ui11,5,4", "ui11,6,4", "ui11,7,4", "ui11,8,4", "ui11,9,4", "ui11,10,4", "ui11,11,4", "ui11,12,4", "ui11,13,4", "ui11,14,4", "ui11,15,4",
        "ui11,0,5", "ui11,1,5", "ui11,2,5", "ui11,3,5", "ui11,4,5", "ui11,5,5", "ui11,6,5", "ui11,7,5", "ui11,8,5", "ui11,9,5", "ui11,10,5", "ui11,11,5", "ui11,12,5", "ui11,13,5", "ui11,14,5", "ui11,15,5",
        "ui11,0,6", "ui11,1,6", "ui11,2,6", "ui11,3,6", "ui11,4,6", "ui11,5,6", "ui11,6,6", "ui11,7,6", "ui11,8,6", "ui11,9,6", "ui11,10,6", "ui11,11,6", "ui11,12,6", "ui11,13,6", "ui11,14,6", "ui11,15,6",
        "ui11,0,7", "ui11,1,7", "ui11,2,7", "ui11,3,7", "ui11,4,7", "ui11,5,7", "ui11,6,7", "ui11,7,7", "ui11,8,7", "ui11,9,7", "ui11,10,7", "ui11,11,7", "ui11,12,7", "ui11,13,7", "ui11,14,7", "ui11,15,7",
        "ui11,0,8", "ui11,1,8", "ui11,2,8", "ui11,3,8", "ui11,4,8", "ui11,5,8", "ui11,6,8", "ui11,7,8", "ui11,8,8", "ui11,9,8", "ui11,10,8", "ui11,11,8", "ui11,12,8", "ui11,13,8", "ui11,14,8", "ui11,15,8",
        "ui11,0,9", "ui11,1,9", "ui11,2,9", "ui11,3,9", "ui11,4,9", "ui11,5,9", "ui11,6,9", "ui11,7,9", "ui11,8,9", "ui11,9,9", "ui11,10,9", "ui11,11,9", "ui11,12,9", "ui11,13,9", "ui11,14,9", "ui11,15,9",
        "ui11,0,10", "ui11,1,10", "ui11,2,10", "ui11,3,10", "ui11,4,10", "ui11,5,10", "ui11,6,10", "ui11,7,10", "ui11,8,10", "ui11,9,10", "ui11,10,10", "ui11,11,10", "ui11,12,10", "ui11,13,10", "ui11,14,10", "ui11,15,10",
        "ui11,0,11", "ui11,1,11", "ui11,2,11", "ui11,3,11", "ui11,4,11", "ui11,5,11", "ui11,6,11", "ui11,7,11", "ui11,8,11", "ui11,9,11", "ui11,10,11", "ui11,11,11", "ui11,12,11", "ui11,13,11", "ui11,14,11", "ui11,15,11",
        "ui11,0,12", "ui11,1,12", "ui11,2,12", "ui11,3,12", "ui11,4,12", "ui11,5,12", "ui11,6,12", "ui11,7,12", "ui11,8,12", "ui11,9,12", "ui11,10,12", "ui11,11,12", "ui11,12,12", "ui11,13,12", "ui11,14,12", "ui11,15,12",
        "ui11,0,13", "ui11,1,13", "ui11,2,13", "ui11,3,13", "ui11,4,13", "ui11,5,13", "ui11,6,13", "ui11,7,13", "ui11,8,13", "ui11,9,13", "ui11,10,13", "ui11,11,13", "ui11,12,13", "ui11,13,13", "ui11,14,13", "ui11,15,13",
        "ui11,0,14", "ui11,1,14", "ui11,2,14", "ui11,3,14", "ui11,4,14", "ui11,5,14", "ui11,6,14", "ui11,7,14", "ui11,8,14", "ui11,9,14", "ui11,10,14", "ui11,11,14", "ui11,12,14", "ui11,13,14", "ui11,14,14", "ui11,15,14",
        "ui11,0,15", "ui11,1,15", "ui11,2,15", "ui11,3,15", "ui11,4,15", "ui11,5,15", "ui11,6,15", "ui11,7,15", "ui11,8,15", "ui11,9,15", "ui11,10,15", "ui11,11,15", "ui11,12,15", "ui11,13,15", "ui11,14,15", "ui11,15,15",
    };
    const std::vector<std::string> arr(tiles);
    tile_load_arr("data/gfx/ui_horiz2.tga", "ui_box11", 8, 8, arr);
}
