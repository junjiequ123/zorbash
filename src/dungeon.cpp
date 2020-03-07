/*
 * Copyright (C) 2018 goblinhack@gmail.com
 * See the LICENSE file for license.
 */

#include "my_dungeon.h"

//
// The algorithm
//
// - Create a cyclic dungeon map. Different 'levels' of the dungeon can be
// cycles with a door of some kind to the next level.
//
//    K         S    D    K
//    1____1____1____2____2    -
//    |    |    |         |
//    |    |    |         |
//    |    |    |         |
//    |    |    |        D|   D
//    1    1____1    -    3____4
//    ?                   |    |
//    ?                   |    |
//    ?                   |    |
//    ?                  K|   E|
//    1____1____2    -    3    4
//
//  - Place initial small rooms
//
//  - Now we know we have a possible level, replace some of the small rooms
//  with larger rooms, so it looks more interesting.
//
//  xDxxxxx                                                         xDxxx
// xx.....D               xDx      xDxxDx                           D...xxx
// D......x               D.xx     x.xx.x      xxDxxx               x.....x
// x......x               x..xx    x....x      x..$.D               x.....x
// xxxxDxxx               x...x    x....x      D....x              xx..x..x
//                        x...xx   xx...x      x....x              x......D
//                        xxx..x    xxx.D      xxxDxx              x...xxxx
//                          xDxx      xDx                          xDxxx
//                                 xDx              xxxxx
//                                 x.x              D...D         xxxxx
//                                xx.xx             x...x         D...D
//   xxxxDxxxxx                  xx...xDx           x...xxxxDxxxx x...xxxxxxxxx
//   x........D                  x......x           x...........D x...........D
//   xxxx..xxxx          xDxxxx  x......xx          x...........x xxxx...xxxxxx
//      D..D             D....D  D.......x          x...........x    D...x
//   xxxx..xxxx          x....xx xDxxxxxxx          x...........x xxxx...x
//   D........x          xx....D                    xxxDxxxxxxxxx x......x
//   xxxxxDxxxx           xx...x                                  xxxDxxxx
//                         xx..x
//           xxxxDx         xxDx  xDxx
//           D....x               D..xx                             xxxxxDx
//           x....D  xxDxx        x...xx                xxxxDxx     x.xx..D
//           x...xx xx...D        x....D                x.....D     x.....x
//           D.xxx  D....x        x.xDxx                D.....x     x.....x
//           xDx    xx..xx        xDx                   x.....x     xxxxxxx
//                   xx.x                               xxxDxxx
//                    xDx
//
//
//  - Drag all the rooms to the center of the map, making sure to keep enough
//  of a gap for corridors
//
//                                                   xDxxx
//                                  xDxxDx           D...xxx
//                  xDxxxxx         x.xx.x           x.....x
//                 xx.....D  xDx    x....x  xxDxxx   x.....x
//                 D......x  D.xx   x....x  x..$.D  xx..x..x
//                 x......x  x..xx  xx...x  D....x  x......D  xxxxx
//                 xxxxDxxx  x...x   xxx.D  x....x  x...xxxx  D...D
//                           x...xx    xDx  xxxDxx  xDxxx     x...xxxxxxxxx
//                           xxx..x                           x...........D
//              xxxxDxxxxx     xDxx    xDx                    xxxx...xxxxxx
//              x........D             x.x      xxxxx            D...x
//              xxxx..xxxx            xx.xx     D...D         xxxx...x
//                 D..D     xDxxxx   xx...xDx   x...x         x......x
//              xxxx..xxxx  D....D   x......x   x...xxxxDxxxx xxxDxxxx
//              D........x  x....xx  x......xx  x...........D
//              xxxxxDxxxx  xx....D  D.......x  x...........x
//                           xx...x  xDxxxxxxx  x...........x
//                            xx..x             x...........x
//                     xxxxDx  xxDx             xxxDxxxxxxxxx
//                     D....x         xDxx
//                     x....D         D..xx            xxxxxDx
//                     x...xx  xxDxx  x...xx  xxxxDxx  x.xx..D
//                     D.xxx  xx...D  x....D  x.....D  x.....x
//                     xDx    D....x  x.xDxx  D.....x  x.....x
//                            xx..xx  xDx     x.....x  xxxxxxx
//                             xx.x           xxxDxxx
//                              xDx
//
//  - Now draw corridors, according to the original node layout. Make sure no
//  corridors overlap or touch.
//
//                                                   xxxxx
//                                  xxxxxx          #D...xxx
//                  xxxxxxx         x.xx.x         ##x.....x
//                 xx.....D# xxx    x....x  xxxxxx## x.....x
//                 x......x##D.xx   x....x  x..$.D# xx..x..x
//                 x......x  x..xx  xx...x #D....x  x......x  xxxxx
//                 xxxxDxxx  x...x   xxx.D##x....x  x...xxxx  x...x
//                   ###     x...xx    xDx  xxxxxx  xDxxx     x...xxxxxxxxx
//                  ##       xxx..x     #            #        x...........x
//              xxxxDxxxxx     xDxx    xDx           #        xxxx...xxxxxx
//              x........x    ###      x.x      xxxxx##      ####D...x
//              xxxx..xxxx   ##       xx.xx     x...x ##     #xxxx...x
//                 x..x     xDxxxx   xx...xxx   x...x  ##    #x......x
//              xxxx..xxxx  x....x   x......x   x...xxxxDxxxx#xxxDxxxx
//              x........x  x....xx  x......xx  x...........D#   #
//              xxxxxDxxxx  xx....D##D.......x  x...........x    #
//                   ??????  xx...x  xxxxxxxxx  x...........x   ##
//                        ??  xx..x             x...........x  ##
//                     xxxxDx  xxxx             xxxDxxxxxxxxx ##
//                     x....x         xxxx         #        ###
//                     x....D#       #D..xx       ##   xxxxxDx
//                     x...xx# xxxxx##x...xx  xxxxDxx  x.xx..x
//                     x.xxx #xx...D# x....x  x.....x  x.....x
//                     xxx   #D....x  x.xxxx  x.....x  x.....x
//                            xx..xx  xxx     x.....x  xxxxxxx
//                             xx.x           xxxxxxx
//                              xxx
//
//

void Dungeon::make_dungeon (void)
{_
    //
    // Create the high level blueprint of the level layout
    //
    create_node_map();

    for (;;) {
        //
        // Reset the list of rooms we can place. We only place one of
        // each possible room once per level
        //
        reset_possible_rooms();

        //
        // Create a cyclic dungeon map.
        //
        create_cyclic_rooms(&grid);
        _ debug("create cyclic rooms");

        //
        // Choose how rooms are linked
        //
        choose_room_doors();
        _ debug("choose room doors");

        //
        // Drag rooms to the center of the map
        //
#if 0
        if (!compress_room_layout_to_center_of_map()) {
            continue;
        }
#endif

        if (compress_room_corridors()) {
            break;
        }

        debug("failed, redo from scratch");
    }

    //
    // Keep track of which tile has which room
    //
    assign_rooms_to_tiles();
    _ debug("assigned rooms to tiles");

    //
    // Wall off secret doors
    //
    block_secret_doors();
    _ debug("blocked secret doors");

    //
    // Remove all doors and then add them back in, but only between
    // depth changes
    //
    remove_all_doors();
    _ debug("remove all doors");

    //
    // Place the rooms back on the map, so if there were any intentional
    // doors removed above then they will reappear.
    //
    room_print_only_doors(&grid);
    _ debug("only doors");

    //
    // Not sure we want this as rooms
    //
    place_doors_between_depth_changes();
    _ debug("add doors between depth changes");

    //
    // Add a perimeter to the level. Helps avoid off by one bugs.
    //
    add_corridor_walls();
    _ debug("add corridor walls");

    add_room_walls();
    _ debug("add room walls");

    LOG("created basic layout:");
    dump();

    //
    // Add a cave as the under-dungeon
    //
    water_gen(20, // fill prob
              10,  // R1
              5,  // R2
              4   /* generations */);

    cave_gen(20, // fill prob
             10,  // R1
             5,  // R2
             3   /* generations */);

    dirt_gen(20, // fill prob
             10,  // R1
             5,  // R2
             4   /* generations */);

    water_fixup();
    add_border();
    add_remaining();

    LOG("final DUNGEON:");
    dump();
}

void Dungeon::debug (const std::string s)
{_
    // return;
    LOG("dungeon (%u) %s", seed, s.c_str());
    LOG("===========================================================");
    dump();
}

//
// Make a dungeon from rooms
//
Dungeon::Dungeon (int map_width, int map_height,
                  int grid_width, int grid_height, int seed) :
    map_width                  (map_width),
    map_height                 (map_height),
    grid_width                 (grid_width),
    grid_height                (grid_height),
    seed                       (seed)
{_
    make_dungeon();
}

//
// Make a dungeon from a single level
//
Dungeon::Dungeon (int level)
{_
    if (level >= (int)PlacedLevel::all_placed_levels.size()) {
        ERR("out of range level %d", level);
        return;
    }
    auto l = get(PlacedLevel::all_placed_levels, level);

    cells.resize(l->width * l->height * MAP_DEPTH, Charmap::SPACE);
    std::fill(cells.begin(), cells.end(), Charmap::SPACE);

    place_level(l);
    dump();
}

int Dungeon::offset (const int x, const int y, const int z)
{
    auto offset = (map_width * map_height) * z;
    offset += (map_width) * y;
    offset += x;

    return (offset);
}

int Dungeon::offset (const int x, const int y)
{
    auto offset = (map_width) * y;
    offset += x;

    return (offset);
}

bool Dungeon::is_oob (const int x, const int y, const int z)
{
    return ((x < 0) || (x >= map_width) ||
            (y < 0) || (y >= map_height) ||
            (z < 0) || (z >= map_depth));
}

bool Dungeon::is_oob (const int x, const int y)
{
    return ((x < 0) || (x >= map_width) ||
            (y < 0) || (y >= map_height));
}

char *Dungeon::cell_addr (const int x, const int y, const int z)
{
    if (is_oob(x, y, z)) {
        return (nullptr);
    }

    return (&getref(cells, offset(x, y, z)));
}

char *Dungeon::cell_addr_fast (const int x, const int y, const int z)
{
    return (&getref(cells, offset(x, y, z)));
}

//
// Puts a tile on the map
//
void Dungeon::putc (const int x, const int y, const int z, const char c)
{
    if (!c) {
        ERR("putting nul char at %d,%d,%d", x, y, z);
    }
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }
    auto p = cell_addr(x, y, z);
    if (p != nullptr) {
        *p = c;
    }
}

//
// Puts a tile on the map
//
void Dungeon::putc_fast (const int x, const int y, const int z, const char c)
{
    auto p = cell_addr_fast(x, y, z);
    if (p != nullptr) {
        *p = c;
    }
}

//
// Gets a tile of the map or None
//
char Dungeon::getc (const int x, const int y, const int z)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }
    auto p = cell_addr(x, y, z);
    if (p != nullptr) {
        return (*p);
    }
    return (Charmap::NONE);
}

//
// Gets a tile of the map or None
//
char Dungeon::getc_fast (const int x, const int y, const int z)
{
    auto p = cell_addr_fast(x, y, z);
    if (p != nullptr) {
        return (*p);
    }
    return (Charmap::NONE);
}

Roomp *Dungeon::cell_rooms_addr (const int x, const int y)
{
    if (is_oob(x, y)) {
        return (nullptr);
    }

    return (&getref(cells_room, offset(x, y)));
}

Roomp *Dungeon::cell_rooms_addr_fast (const int x, const int y)
{
    return (&getref(cells_room, offset(x, y)));
}

void Dungeon::putr (const int x, const int y, Roomp r)
{
    auto p = cell_rooms_addr(x, y);
    if (p != nullptr) {
        *p = r;
    }
}

Roomp Dungeon::getr (const int x, const int y)
{
    auto p = cell_rooms_addr(x, y);
    if (p != nullptr) {
        return (*p);
    }
    return (nullptr);
}

Roomp Dungeon::getr_fast (const int x, const int y)
{
    auto p = cell_rooms_addr_fast(x, y);
    if (p != nullptr) {
        return (*p);
    }
    return (nullptr);
}

bool Dungeon::is_anything_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_anything_at (const int x, const int y, const int z)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    auto c = getc(x, y, z);
    if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
        return true;
    }
    return false;
}

int Dungeon::get_grid_depth_at (const int x, const int y)
{
    if (!nodes) {
        return (0);
    }

    auto r = getr(x, y);
    if (r) {
        return (r->depth);
    }
    return (0);
}

bool Dungeon::is_floor (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_floor) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_corridor (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_corridor) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_corridor_fast (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_corridor) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_dirt (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_dirt) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_dirt_fast (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_dirt) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_secret_corridor_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_secret_corridor) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_wall (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    auto d = MAP_DEPTH_WALLS;
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);
    return (v.is_wall);
}

bool Dungeon::is_monst (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_monst) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_food (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_food) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_blood (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_blood) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_rock (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_rock) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_door (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_door) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_secret_door (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_secret_door) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_entrance_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_entrance) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_floor_deco_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_floor_deco) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_wall_deco_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_wall_deco) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_exit_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_exit) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_lava (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_lava) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_chasm (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_chasm) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_water (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_water) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_deep_water (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_deep_water) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_hazard (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_deep_water) {
            return true;
        }
        if (v.is_water) {
            return true;
        }
        if (v.is_chasm) {
            return true;
        }
        if (v.is_lava) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_treasure_at (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_treasure) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_key (const int x, const int y)
{
    if (is_oob(x, y)) {
        ERR("oob %s at (%d,%d)", __FUNCTION__, x, y);
    }

    for (auto d = 0; d < map_depth; d++) {
        auto c = getc(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_key) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_anything_at_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_anything_at_fast (const int x, const int y, const int z)
{
    auto c = getc_fast(x, y, z);
    if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
        return true;
    }
    return false;
}

bool Dungeon::is_floor_fast (const int x, const int y)
{
    const auto d = MAP_DEPTH_FLOOR;
    auto c = getc_fast(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    return (v.is_floor);
}

bool Dungeon::is_wall_fast (const int x, const int y)
{
    auto d = MAP_DEPTH_WALLS;
    auto c = getc_fast(x, y, d);
    auto v = get(Charmap::all_charmaps, c);
    return (v.is_wall);
}

bool Dungeon::is_door_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_door) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_entrance_at_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_entrance) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_exit_at_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_exit) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_lava_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_lava) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_chasm_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_chasm) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_water_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_water) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_deep_water_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_deep_water) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_treasure_at_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_treasure) {
            return true;
        }
    }
    return false;
}

bool Dungeon::is_key_fast (const int x, const int y)
{
    for (auto d = 0; d < map_depth; d++) {
        auto c = getc_fast(x, y, d);
        auto v = get(Charmap::all_charmaps, c);

        if (v.is_key) {
            return true;
        }
    }
    return false;
}

void Dungeon::create_node_map (void)
{
    if (grid_width > GRID_WIDTH) {
        ERR("nodes width overflow. got %d, max %d",
            grid_width, GRID_WIDTH);
    }

    if (grid_height > GRID_HEIGHT) {
        ERR("nodes height overflow. got %d, max %d",
            grid_height, GRID_HEIGHT);
    }

    nodes = new Nodes(grid_width, grid_height);
}

void Dungeon::dump (void)
{_
    if (!dungeon_debug) {
        return;
    }

    if (0) {
    LOG("DUNGEON: seed %u (with room depth)", seed);
    //printf("DUNGEON: seed %u (with room depth)\n", seed);
    return;
    for (auto y = 0; y < map_height; y++) {
        std::string s;
        for (auto x = 0; x < map_width; x++) {
            bool got_one = false;
            for (auto d = map_depth - 1; d >= 0; d--) {
                if (!is_anything_at(x, y, d)) {
                    continue;
                }

                auto m = getc(x, y, d);
                auto cr = get(Charmap::all_charmaps, m);
                auto c = cr.c;

                if (!c) {
                    ERR("unknown map char 0x%x/%c at x %d, y %d, depth %d",
                        m, m, x, y, d);
                }

                if (nodes) {
                    if (!(x % 2) && !(y % 2)) {
                        if (!is_wall(x, y) && is_floor(x, y)) {
                            auto X = (x - MAP_BORDER) / ROOM_WIDTH;
                            auto Y = (y - MAP_BORDER) / ROOM_HEIGHT;
                            auto n = nodes->getn(X, Y);
                            if (n) {
                                c = '0' + n->depth;
                            }
                        }
                    }
                }

                if (!((x-MAP_BORDER) % ROOM_WIDTH) ||
                    !((y-MAP_BORDER) % ROOM_HEIGHT)) {
                    if (is_wall(x, y)) {
                        c = 'X';
                    }
                }

                s += c;
                got_one = true;
                break;
            }
            if (!got_one) {
                s += " ";
            }
        }
        if (s != "") {
            LOG("[%s]", s.c_str());
            //printf("[%s]\n", s.c_str());
        }
    }}

    //
    // Pass 2 without room depths
    //
    LOG("DUNGEON: seed %u (more readable version)", seed);
    //printf("DUNGEON: seed %u (more readable version)\n", seed);
    for (auto y = 0; y < map_height; y++) {
        std::string s;
        for (auto x = 0; x < map_width; x++) {
            bool got_one = false;
            for (auto d = map_depth - 1; d >= 0; d--) {
                if (!is_anything_at(x, y, d)) {
                    continue;
                }

                auto m = getc(x, y, d);
                auto cr = get(Charmap::all_charmaps, m);
                auto c = cr.c;

                if (!c) {
                    ERR("unknown map char %c at x %d, y %d, depth %d",
                        m, x, y, d);
                }

                s += c;
                got_one = true;
                break;
            }
            if (!got_one) {
                s += " ";
            }
        }
        if (s != "") {
            LOG("[%s]", s.c_str());
            //printf("[%s]\n", s.c_str());
        }
    }
}

void Dungeon::reset_possible_rooms (void)
{
    cells.resize(map_width * map_height * MAP_DEPTH,
                 Charmap::SPACE);
    cells_room.resize(map_width * map_height, nullptr);

    std::fill(cells.begin(), cells.end(), Charmap::SPACE);
    std::fill(cells_room.begin(), cells_room.end(), nullptr);

    for (auto r : Room::all_rooms) {
        r->placed = false;
        r->skip = false;
        r->depth = 0;

        r->which_secret_door_up = 0;
        r->which_secret_door_down = 0;
        r->which_secret_door_left = 0;
        r->which_secret_door_right = 0;
        r->which_door_up = 0;
        r->which_door_down = 0;
        r->which_door_left = 0;
        r->which_door_right = 0;

        r->left_room = nullptr;
        r->right_room = nullptr;
        r->up_room = nullptr;
        r->down_room = nullptr;

        r->secret_left_room = nullptr;
        r->secret_right_room = nullptr;
        r->secret_up_room = nullptr;
        r->secret_down_room = nullptr;
    }
}

void Dungeon::room_print_at (Roomp r, int x, int y)
{_
    r->at.x = x;
    r->at.y = y;
    for (auto z = 0; z < MAP_DEPTH; z++) {
        for (auto dy = 0; dy < r->height; dy++) {
            for (auto dx = 0; dx < r->width; dx++) {
                auto c = get(r->data, dx, dy, z);
                if (c && (c != Charmap::SPACE)) {
                    putc(x + dx, y + dy, z, c);
                }
            }
        }
    }
}

void Dungeon::room_print_only_doors_at (Roomp r, int x, int y)
{_
    for (auto z = 0; z < MAP_DEPTH; z++) {
        for (auto dy = 0; dy < r->height; dy++) {
            for (auto dx = 0; dx < r->width; dx++) {
                auto c = get(r->data, dx, dy, z);
                if (c == Charmap::DOOR) {
                    putc(x + dx, y + dy, z, c);
                }
            }
        }
    }
}

void Dungeon::room_print_only_doors (Grid *g)
{_
    for (auto x = 0; x < grid_width; x++) {
        for (auto y = 0; y < grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            Roomp r = get(g->node_rooms, x, y);
            if (r) {
                room_print_only_doors_at(r, r->at.x, r->at.y);
            }
        }
    }
}

void Dungeon::rooms_print_all (Grid *g)
{_
    std::fill(cells.begin(), cells.end(), Charmap::SPACE);

    for (auto x = 0; x < grid_width; x++) {
        for (auto y = 0; y < grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            Roomp r = get(g->node_rooms, x, y);
            auto rx = x * ROOM_WIDTH + MAP_BORDER;
            auto ry = y * ROOM_HEIGHT + MAP_BORDER;
            room_print_at(r, rx, ry);
        }
    }
}

bool Dungeon::room_is_a_candidate (const Node *n, Roomp r)
{
    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto o = get(grid.node_rooms, x, y);
            if (o == r) {
                return (false);
            }
        }
    }

    if ((n->has_door_down || n->has_secret_exit_down) &&
        !r->doors_down.size()) {
        return (false);
    }
    if ((n->has_door_up || n->has_secret_exit_up) &&
        !r->doors_up.size()) {
        return (false);
    }
    if ((n->has_door_left || n->has_secret_exit_left) &&
        !r->doors_left.size()) {
        return (false);
    }
    if ((n->has_door_right || n->has_secret_exit_right) &&
        !r->doors_right.size()) {
        return (false);
    }
    if (n->dir_left != r->dir_left) {
        return (false);
    }
    if (n->dir_right != r->dir_right) {
        return (false);
    }
    if (n->dir_up != r->dir_up) {
        return (false);
    }
    if (n->dir_down != r->dir_down) {
        return (false);
    }
    if (n->is_exit != r->is_exit) {
        return (false);
    }
    if (n->is_entrance != r->is_entrance) {
        return (false);
    }
    if (n->is_lock != r->is_lock) {
        return (false);
    }
    if (n->is_key != r->is_key) {
        return (false);
    }
    if (n->is_secret != r->is_secret) {
        return (false);
    }
    if (n->depth != r->depth) {
        return (false);
    }
    return (true);
}

bool Dungeon::room_is_a_candidate_less_restrictive (const Node *n, Roomp r)
{
    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto o = get(grid.node_rooms, x, y);
            if (o == r) {
                return (false);
            }
        }
    }

    if ((n->has_door_down || n->has_secret_exit_down) &&
        !r->doors_down.size()) {
        return (false);
    }
    if ((n->has_door_up || n->has_secret_exit_up) &&
        !r->doors_up.size()) {
        return (false);
    }
    if ((n->has_door_left || n->has_secret_exit_left) &&
        !r->doors_left.size()) {
        return (false);
    }
    if ((n->has_door_right || n->has_secret_exit_right) &&
        !r->doors_right.size()) {
        return (false);
    }
    if (r->dir_left) {
        return (false);
    }
    if (r->dir_right) {
        return (false);
    }
    if (r->dir_up) {
        return (false);
    }
    if (r->dir_down) {
        return (false);
    }
    if (n->is_exit != r->is_exit) {
        return (false);
    }
    if (n->is_entrance != r->is_entrance) {
        return (false);
    }
    if (n->is_lock != r->is_lock) {
        return (false);
    }
    if (n->is_key != r->is_key) {
        return (false);
    }
    return (true);
}

bool Dungeon::solve (int x, int y, Grid *g)
{
    auto n = nodes->getn(x, y);

    if (!nodes->node_is_a_room(n)) {
        return (true);
    }

    if (get(g->node_rooms, x, y)) {
        return (true);
    }

    std::vector<Roomp> candidates;

    for (auto r : Room::all_rooms) {
        if (!room_is_a_candidate(n, r)) {
            continue;
        }

        candidates.push_back(r);
    }

    auto ncandidates = candidates.size();
    if (!ncandidates) {
        for (auto r : Room::all_rooms) {
            if (!room_is_a_candidate_less_restrictive(n, r)) {
                continue;
            }

            candidates.push_back(r);
        }

        ncandidates = candidates.size();
        if (!ncandidates) {
            rooms_print_all(g);
            dump();
            ERR("no grid room candidates at (%d,%d)", x, y);
            return (false);
        }
    }

    auto ri = random_range(0, ncandidates);
    auto r = get(candidates, ri);
    set(g->node_rooms, x, y, r);

    if (n->has_door_down) {
        Grid old;
        std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
        if (!solve(x, y+1, g)) {
            std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms));
        }
    }
    if (n->has_door_up) {
        Grid old;
        std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
        if (!solve(x, y-1, g)) {
            std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms));
        }
    }
    if (n->has_door_right) {
        Grid old;
        std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
        if (!solve(x+1, y, g)) {
            std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms));
        }
    }
    if (n->has_door_left) {
        Grid old;
        std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
        if (!solve(x-1, y, g)) {
            std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms));
        }
    }
    return (true);
}

bool Dungeon::create_cyclic_rooms (Grid *g)
{
    for (auto x = 0; x < grid_width; x++) {
        for (auto y = 0; y < grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (!n->is_entrance) {
                continue;
            }
            if (!solve(x, y, g)) {
                dump();
                ERR("could not solve level at %d,%d", x, y);
            }
            break;
        }
    }

    for (auto x = 0; x < grid_width; x++) {
        for (auto y = 0; y < grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (!n->is_secret) {
                continue;
            }
            solve(x, y, g);
        }
    }

    rooms_print_all(g);

    return (true);
}

void Dungeon::add_border (void)
{
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_BORDER; x++) {
            if (! is_anything_at_fast(x, y)) {
                putc(x, y, MAP_DEPTH_WALLS, Charmap::ROCK);
            }
            if (! is_anything_at_fast(MAP_WIDTH - (x+1), y)) {
                putc(MAP_WIDTH - (x+1), y, MAP_DEPTH_WALLS, Charmap::ROCK);
            }
        }
    }
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_BORDER; y++) {
            if (! is_anything_at_fast(x, y)) {
                putc(x, y, MAP_DEPTH_WALLS, Charmap::ROCK);
            }
            if (! is_anything_at_fast(x, MAP_HEIGHT - (y+1))) {
                putc(x, MAP_HEIGHT - (y+1), MAP_DEPTH_WALLS, Charmap::ROCK);
            }
        }
    }

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_ROCK_BORDER; x++) {
            putc(x, y, MAP_DEPTH_WALLS, Charmap::ROCK);
            putc(MAP_WIDTH - (x+1), y, MAP_DEPTH_WALLS, Charmap::ROCK);
        }
    }
    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_ROCK_BORDER; y++) {
            putc(x, y, MAP_DEPTH_WALLS, Charmap::ROCK);
            putc(x, MAP_HEIGHT - (y+1), MAP_DEPTH_WALLS, Charmap::ROCK);
        }
    }
}

void Dungeon::add_corridor_walls (void)
{
    for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
        for (auto x = 1; x < MAP_WIDTH - 1; x++) {
            if (is_wall_fast(x, y)) {
                continue;
            }
            if (is_corridor_fast(x, y)) {
                if (!is_anything_at_fast(x - 1, y - 1)) {
                    putc(x - 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x, y - 1)) {
                    putc(x, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x + 1, y - 1)) {
                    putc(x + 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }

                if (!is_anything_at_fast(x - 1, y)) {
                    putc(x - 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x + 1, y)) {
                    putc(x + 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                }

                if (!is_anything_at_fast(x - 1, y + 1)) {
                    putc(x - 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x, y + 1)) {
                    putc(x, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x + 1, y + 1)) {
                    putc(x + 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
            }
        }
    }
}

void Dungeon::add_room_walls (void)
{
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            if (is_wall_fast(x, y)) {
                continue;
            }
            if (is_floor_fast(x, y)) {
                if (!is_anything_at_fast(x - 1, y - 1)) {
                    putc(x - 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x, y - 1)) {
                    putc(x, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x + 1, y - 1)) {
                    putc(x + 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }

                if (!is_anything_at_fast(x - 1, y)) {
                    putc(x - 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x + 1, y)) {
                    putc(x + 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                }

                if (!is_anything_at_fast(x - 1, y + 1)) {
                    putc(x - 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x, y + 1)) {
                    putc(x, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at_fast(x + 1, y + 1)) {
                    putc(x + 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                }
            }
        }
    }
}

//
// Find which doors we want to use for a room
//
void Dungeon::choose_room_doors (void)
{
    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            if (n->depth == nodes->depth_obstacle) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);

            if (n->has_door_down) {
                auto o = get(grid.node_rooms, x, y+1);
                if (!o) {
                    _ debug("bug");
                    ERR("had exit down at %d,%d, but no node exists", x, y);
                }
                auto rdoori = random_range(0, r->doors_down.size());
                auto odoori = random_range(0, o->doors_up.size());
                if (rdoori >= r->doors_down.size()) {
                    _ debug("bug");
                    ERR("bug");
                }
                if (odoori >= o->doors_up.size()) {
                    _ debug("bug");
                    ERR("bug");
                }

                r->which_door_down = rdoori;
                o->which_door_up = odoori;

                r->down_room = o;
                o->up_room = r;
            }

            if (n->has_door_right) {
                auto o = get(grid.node_rooms, x+1, y);
                if (!o) {
                    _ debug("bug");
                    ERR("had exit right at %d,%d, but no node exists", x, y);
                }
                auto rdoori = random_range(0, r->doors_right.size());
                auto odoori = random_range(0, o->doors_left.size());
                if (rdoori >= r->doors_right.size()) {
                    _ debug("bug");
                    ERR("bug");
                }
                if (odoori >= o->doors_left.size()) {
                    _ debug("bug");
                    ERR("bug");
                }

                r->which_door_right = rdoori;
                o->which_door_left = odoori;

                r->right_room = o;
                o->left_room = r;
            }

            if (n->has_secret_exit_down) {
                auto o = get(grid.node_rooms, x, y+1);
                if (!o) {
                    _ debug("bug");
                    ERR("had secret exit down at %d,%d, but no node exists", x, y);
                }
                auto rdoori = random_range(0, r->doors_down.size());
                auto odoori = random_range(0, o->doors_up.size());
                if (rdoori >= r->doors_down.size()) {
                    _ debug("bug");
                    ERR("bug, room %d, down door index %d size %d",
                        r->roomno, (int)rdoori, (int)r->doors_down.size());
                }
                if (odoori >= o->doors_up.size()) {
                    _ debug("bug");
                    ERR("bug, room %d, up door index %d size %d",
                        r->roomno, (int)odoori, (int)r->doors_up.size());
                }

                r->which_secret_door_down = rdoori;
                o->which_secret_door_up = odoori;

                r->secret_down_room = o;
                o->secret_up_room = r;
            }

            if (n->has_secret_exit_right) {
                auto o = get(grid.node_rooms, x+1, y);
                if (!o) {
                    _ debug("bug");
                    ERR("had secret exit right at %d,%d, but no node exists", x, y);
                }
                auto rdoori = random_range(0, r->doors_right.size());
                auto odoori = random_range(0, o->doors_left.size());
                if (rdoori >= r->doors_right.size()) {
                    _ debug("bug");
                    ERR("bug, room %d, right door index %d size %d",
                        r->roomno, (int)rdoori, (int)r->doors_right.size());
                }
                if (odoori >= o->doors_left.size()) {
                    _ debug("bug");
                    ERR("bug, room %d, left door index %d size %d",
                        r->roomno, (int)odoori, (int)r->doors_left.size());
                }

                r->which_secret_door_right = rdoori;
                o->which_secret_door_left = odoori;

                r->secret_right_room = o;
                o->secret_left_room = r;
            }
        }
    }
}

void Dungeon::save_level (void)
{
    std::copy(mbegin(cells), mend(cells), mbegin(cells_saved));

    for (unsigned int rs = 0;
            rs < (unsigned int) all_placed_rooms.size(); rs++) {
        auto r = get(all_placed_rooms, rs);
        r->rollback_at = r->at;
    }
}

void Dungeon::restore_level (void)
{
    std::copy(mbegin(cells_saved), mend(cells_saved), mbegin(cells));

    for (unsigned int rs = 0;
            rs < (unsigned int) all_placed_rooms.size(); rs++) {
        auto r = get(all_placed_rooms, rs);
        r->at = r->rollback_at;
    }
}


int Dungeon::draw_corridor (point start, point end, char w)
{
    Dmap d {};
#if 0
    if (w == Charmap::CORRIDOR) {
        LOG("create corridor, between %d,%d and %d,%d",
            start.x, start.y,
            end.x, end.y);
    } else {
        LOG("create secret corridor, between %d,%d and %d,%d",
            start.x, start.y,
            end.x, end.y);
    }
#endif

    point dmap_start = start;
    point dmap_end = end;

    int minx, miny, maxx, maxy;
    if (dmap_start.x < dmap_end.x) {
        minx = dmap_start.x;
        maxx = dmap_end.x;
    } else {
        minx = dmap_end.x;
        maxx = dmap_start.x;
    }
    if (dmap_start.y < dmap_end.y) {
        miny = dmap_start.y;
        maxy = dmap_end.y;
    } else {
        miny = dmap_end.y;
        maxy = dmap_start.y;
    }

    auto border = 2;
    minx -= border;
    miny -= border;
    maxx += border;
    maxy += border;

    if (minx < 0) {
        minx = 0;
    }
    if (miny < 0) {
        miny = 0;
    }
    if (maxx >= map_width) {
        maxx = map_width - 1;
    }
    if (maxy >= map_height) {
        maxy = map_height - 1;
    }

    //
    // Set up obstacles for the corridor search
    //
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            if (is_anything_at_fast(x, y)) {
                set(d.val, x, y, DMAP_IS_WALL);
            } else {
                set(d.val, x, y, DMAP_IS_PASSABLE);
            }
        }
    }

    //
    // Ensure adjoining corridors are not possible
    //
    for (auto y = miny + 1; y < maxy - 1; y++) {
        for (auto x = minx + 1; x < maxx - 1; x++) {
            if (is_corridor_fast(x, y)) {
                set(d.val, x-1, y, DMAP_IS_WALL);
                set(d.val, x, y-1, DMAP_IS_WALL);
                set(d.val, x, y, DMAP_IS_WALL);
                set(d.val, x, y+1, DMAP_IS_WALL);
                set(d.val, x+1, y, DMAP_IS_WALL);
            }
        }
    }

    dmap_start = point(minx, miny);
    dmap_end = point(maxx, maxy);

    set(d.val, end.x, end.y, DMAP_IS_GOAL);
    set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

    dmap_process(&d, dmap_start, dmap_end);

    auto p = dmap_solve(&d, start);
#if 0
    dmap_print(&d, start, dmap_start, dmap_end);
#endif

    //
    // Too long a corridor?
    //
#if 1
    if (p.size() > 25) {
        for (auto c : p) {
            putc(c.x, c.y, MAP_DEPTH_FLOOR, Charmap::DEBUG);
        }
        DBG("failed to create corridor, too long a corridor");
        return (0);
    }
#endif

    //
    // Check we can reach the end point
    //
    bool got_goal = false;
    for (auto c : p) {
        if (c == end) {
            got_goal = true;
            break;
        }
    }

    if (!got_goal) {
        for (auto c : p) {
            putc(c.x, c.y, MAP_DEPTH_FLOOR, Charmap::DEBUG);
        }
        putc(start.x, start.y, MAP_DEPTH_WALLS, Charmap::DEBUG);
        putc(end.x, end.y, MAP_DEPTH_WALLS, Charmap::DEBUG);

        DBG("DUNGEON: failed to create corridor, end not found between %d,%d and %d,%d",
            start.x, start.y, end.x, end.y);
        return (0);
    }

    for (auto c : p) {
        putc(c.x, c.y, MAP_DEPTH_FLOOR, w);
    }

    putc(start.x, start.y, MAP_DEPTH_WALLS, Charmap::DOOR);
    putc(end.x, end.y, MAP_DEPTH_WALLS, Charmap::DOOR);
    DBG("DUNGEON: placed corridor len %d", (int)p.size());
    return (p.size());
}

//
// Join the corridors of each room, return the total lenght of all corridors
//
int Dungeon::draw_corridors (void)
{
    for (auto x = 0; x < map_width; x++) {
        for (auto y = 0; y < map_height; y++) {
            auto c = getc(x, y, MAP_DEPTH_WALLS);
            if ((c == Charmap::DOOR_UP) ||
                (c == Charmap::DOOR_DOWN) ||
                (c == Charmap::DOOR_LEFT) ||
                (c == Charmap::DOOR_RIGHT)) {
                putc(x, y, MAP_DEPTH_WALLS, Charmap::WALL);
            }
        }
    }

    auto total_len = 0;

    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {

            auto n = nodes->getn(x, y);
            if (!n->depth) {
                continue;
            }

            if (n->depth == nodes->depth_obstacle) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);

            if (n->has_door_down) {
                auto o = get(grid.node_rooms, x, y+1);

                auto rdoori = r->which_door_down;
                auto odoori = o->which_door_up;

                auto rdoor = get(r->doors_down, rdoori);
                auto odoor = get(o->doors_up, odoori);

                auto start = r->at + rdoor;
                auto end = o->at + odoor;

                r->down_door_at = start;
                o->up_door_at = end;

                auto len = draw_corridor(start, end, Charmap::CORRIDOR);
                if (!len) {
                    return (0);
                }
                total_len += len;
            }

            if (n->has_door_right) {
                auto o = get(grid.node_rooms, x+1, y);

                auto rdoori = r->which_door_right;
                auto odoori = o->which_door_left;

                auto rdoor = get(r->doors_right, rdoori);
                auto odoor = get(o->doors_left, odoori);

                auto start = r->at + rdoor;
                auto end = o->at + odoor;

                r->right_door_at = start;
                o->left_door_at = end;

                auto len = draw_corridor(start, end, Charmap::CORRIDOR);
                if (!len) {
                    return (0);
                }
                total_len += len;
            }

            if (n->has_secret_exit_down) {
                auto o = get(grid.node_rooms, x, y+1);

                auto rdoori = r->which_secret_door_down;
                auto odoori = o->which_secret_door_up;

                auto rdoor = get(r->doors_down, rdoori);
                auto odoor = get(o->doors_up, odoori);

                auto start = r->at + rdoor;
                auto end = o->at + odoor;

                r->down_secret_door_at = start;
                o->up_secret_door_at = end;

                auto len = draw_corridor(start, end, Charmap::SECRET_CORRIDOR);
                if (!len) {
                    return (0);
                }
                total_len += len;
            }

            if (n->has_secret_exit_right) {
                auto o = get(grid.node_rooms, x+1, y);

                auto rdoori = r->which_secret_door_right;
                auto odoori = o->which_secret_door_left;

                auto rdoor = get(r->doors_right, rdoori);
                auto odoor = get(o->doors_left, odoori);

                auto start = r->at + rdoor;
                auto end = o->at + odoor;

                r->right_secret_door_at = start;
                o->left_secret_door_at = end;

                auto len = draw_corridor(start, end, Charmap::SECRET_CORRIDOR);
                if (!len) {
                    return (0);
                }
                total_len += len;
            }
        }
    }

    return (total_len);
}

void Dungeon::center_room_layout (void)
{
    auto minx = map_width;
    auto miny = map_height;
    auto maxx = 0;
    auto maxy = 0;

    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);
            if (!r) {
                continue;
            }

            if (r->at.x < minx) {
                minx = r->at.x;
            }
            if (r->at.y < miny) {
                miny = r->at.y;
            }
            if (r->at.x + r->width > maxx) {
                maxx = r->at.x + r->width;
            }
            if (r->at.y + r->height > maxy) {
                maxy = r->at.y + r->height;
            }
        }
    }

    auto dx = (map_width - (maxx - minx)) / 2;
    auto dy = (map_height - (maxy - miny)) / 2;

    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);
            if (!r) {
                continue;
            }

            r->at.x -= minx;
            r->at.y -= miny;

            r->at.x += dx;
            r->at.y += dy;
        }
    }
}

//
// Dump a room onto the level. No checks
//
void Dungeon::place_room (Roomp r, int x, int y)
{
    for (auto dz = 0 ; dz < MAP_DEPTH; dz++) {
        for (auto dy = 0; dy < r->height; dy++) {
            for (auto dx = 0; dx < r->width; dx++) {
                auto c = get(r->data, dx, dy, dz);
                if ((c != Charmap::SPACE) && (c != Charmap::NONE)) {
                    putc_fast(x + dx, y + dy, dz, c);
                }
            }
        }
    }

    for (auto dy = 0; dy < r->height; dy++) {
        for (auto dx = 0; dx < r->width; dx++) {
            auto f = get(r->data, dx, dy, MAP_DEPTH_FLOOR);
            auto d = get(r->data, dx, dy, MAP_DEPTH_WALLS);
            if ((d == Charmap::DOOR_UP) ||
                (d == Charmap::DOOR_DOWN) ||
                (d == Charmap::DOOR_LEFT) ||
                (d == Charmap::DOOR_RIGHT)) {
                //
                // Do not wrap doors in walls so we can move the rooms closer
                //
            } else if (f != Charmap::SPACE) {
                if (!is_anything_at(x + dx - 1, y + dy - 1)) {
                    putc_fast(x + dx - 1, y + dy - 1,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at(x + dx, y + dy - 1)) {
                    putc_fast(x + dx, y + dy - 1,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at(x + dx + 1, y + dy - 1)) {
                    putc_fast(x + dx + 1, y + dy - 1,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at(x + dx - 1, y + dy)) {
                    putc_fast(x + dx - 1, y + dy,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at(x + dx + 1, y + dy)) {
                    putc_fast(x + dx + 1, y + dy,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at(x + dx - 1, y + dy + 1)) {
                    putc_fast(x + dx - 1, y + dy + 1,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at(x + dx, y + dy + 1)) {
                    putc_fast(x + dx, y + dy + 1,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
                if (!is_anything_at(x + dx + 1, y + dy + 1)) {
                    putc_fast(x + dx + 1, y + dy + 1,
                              MAP_DEPTH_WALLS, Charmap::WALL);
                }
            }
        }
    }
}

void Dungeon::place_level (PlacedLevelp l)
{
    if ((l->width > MAP_WIDTH) || (l->height > MAP_HEIGHT)) {
        ERR("level has bad size %d,%d", l->width, l->height);
    }

    for (auto z = 0 ; z < MAP_DEPTH; z++) {
        for (auto y = 0; y < l->height; y++) {
            for (auto x = 0; x < l->width; x++) {
                auto c = get(l->data, x, y, z);
                if (c && (c != Charmap::SPACE)) {
                    putc(x, y, z, c);
                }
            }
        }
    }
}

//
// Dump a room onto the level along with its roomno. Done when we
// have finalized positions of rooms.
//
void Dungeon::map_place_room_ptr (Roomp r, int x, int y)
{
    if (!r) {
        ERR("no room to place");
    }

    for (auto dz = 0 ; dz < MAP_DEPTH; dz++) {
        for (auto dy = 0; dy < r->height; dy++) {
            for (auto dx = 0; dx < r->width; dx++) {
                auto c = get(r->data, dx, dy, dz);
                if (c != Charmap::SPACE) {
                    putr(x + dx, y + dy, r);
                }
            }
        }
    }
}

//
// Check for room overlaps
//
bool Dungeon::can_place_room (Roomp r, int x, int y)
{
    if (x < 0) {
        return false;
    }
    if (x + r->width >= map_width) {
        return false;
    }

    if (y < 0) {
        return false;
    }
    if (y + r->height >= map_height) {
        return false;
    }

    for (auto dz = 0 ; dz < MAP_DEPTH; dz++) {
        for (auto dy = 0; dy < r->height; dy++) {
            for (auto dx = 0; dx < r->width; dx++) {
                auto c = get(r->data, dx, dy, dz);
                if (c != Charmap::SPACE) {
                    if (is_anything_at(x + dx, y + dy)) {
                        return false;
                    }

                    if (is_wall(x + dx - 1, y + dy) ||
                        is_wall(x + dx + 1, y + dy) ||
                        is_wall(x + dx, y + dy - 1) ||
                        is_wall(x + dx, y + dy + 1)) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

//
// Repeat placing all rooms bar one random one. Try to move
// that random one closer to the center. Repeat.
//
bool Dungeon::compress_room_layout_to_center_of_map (void)
{
    auto mx = map_width / 2;
    auto my = map_height / 2;
    auto delta = 1;

    all_placed_rooms.resize(0);

    for (auto r : Room::all_rooms) {
        r->placed = false;
    }

    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);
            if (!r) {
                continue;
            }

            all_placed_rooms.push_back(r);
            r->placed = true;
        }
    }

    //
    // Make sure we start with a solvable room
    //
    save_level();
    if (!draw_corridors()) {
        _ debug("level before adding corridors is NOT solvable");
        return (false);
    }

    restore_level();
    _ debug("level before adding corridors is solvable");

    auto failed_attempts = 0;
    auto attempts_to_move_rooms_closer = 100;

    choose_room_doors();

    while (attempts_to_move_rooms_closer--) {

        center_room_layout();

        for (unsigned int rs = 0;
             rs < (unsigned int) all_placed_rooms.size();
             rs++) {

            auto r = get(all_placed_rooms, rs);
            auto skip_roomno = r->roomno;

            std::fill(cells.begin(), cells.end(), Charmap::SPACE);

            auto moved = false;

            //
            // Place all except one room
            //
            auto ri = 0;
            for (auto x = 0; x < nodes->grid_width; x++) {
                for (auto y = 0; y < nodes->grid_height; y++) {

                    auto n = nodes->getn(x, y);
                    if (n->depth <= 0 ) {
                        continue;
                    }

                    auto r = get(all_placed_rooms, ri++);
                    if (r->roomno == skip_roomno) {
                        continue;
                    }

                    place_room(r, r->at.x, r->at.y);
                }
            }

            //
            // Place the room we want to move
            //
            ri = 0;
            for (auto x = 0; x < nodes->grid_width; x++) {
                for (auto y = 0; y < nodes->grid_height; y++) {

                    auto n = nodes->getn(x, y);
                    if (!n->depth) {
                        continue;
                    }

                    //
                    // water etc..
                    //
                    if (n->depth == nodes->depth_obstacle) {
                        continue;
                    }

                    auto r = get(all_placed_rooms, ri++);
                    if (r->roomno != skip_roomno) {
                        continue;
                    }

                    if (r->at.x + r->width > mx) {
                        if (can_place_room(r, r->at.x - delta, r->at.y)) {
                            r->at.x--;
                            place_room(r, r->at.x, r->at.y);
                            moved = true;
                            break;
                        }
                    }

                    if (r->at.x < mx) {
                        if (can_place_room(r, r->at.x + delta, r->at.y)) {
                            r->at.x++;
                            place_room(r, r->at.x, r->at.y);
                            moved = true;
                            break;
                        }
                    }

                    if (r->at.y + r->height > my) {
                        if (can_place_room(r, r->at.x, r->at.y - delta)) {
                            r->at.y--;
                            place_room(r, r->at.x, r->at.y);
                            moved = true;
                            break;
                        }
                    }

                    if (r->at.y < my) {
                        if (can_place_room(r, r->at.x, r->at.y + delta)) {
                            r->at.y++;
                            place_room(r, r->at.x, r->at.y);
                            moved = true;
                            break;
                        }
                    }

                    place_room(r, r->at.x, r->at.y);
                    break;
                }
            }

            if (!moved) {
                continue;
            }

            //
            // Ok we've moved one room. If we can still place corridors
            // then we can keep going. If not, rollback the room to the
            // last that was solvable.
            //
            std::vector<char> cells_ok;
            std::copy(mbegin(cells), mend(cells), mbegin(cells_ok));

            if (!draw_corridors()) {
                LOG("failed to placing corridors, rollback");
                restore_level();
            } else {
                _ debug("success, placed corridors");
                failed_attempts = 0;
                std::copy(mbegin(cells_ok), mend(cells_ok), mbegin(cells));
                save_level();
            }
        }
    }

    _ debug("success, placed compressed layout");
    return (true);
}

bool Dungeon::compress_room_corridors (void)
{
    auto delta = 1;

    all_placed_rooms.resize(0);

    for (auto r : Room::all_rooms) {
        r->placed = false;
    }

    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);
            if (!r) {
                continue;
            }

            all_placed_rooms.push_back(r);
            r->placed = true;
        }
    }

    //
    // Make sure we start with a solvable room
    //
    save_level();
    auto corridor_count = draw_corridors();
    if (!corridor_count) {
        _ debug("level before adding corridors is NOT solvable");
        return (false);
    }

    dump();
    _ debug("level before adding shorter corridors is solvable");
    restore_level();

    auto failed_to_place_all_corridors = 0;
    auto failed_to_make_shorter_corridors = 0;
    auto attempts_to_move_rooms_closer = 100;

    choose_room_doors();

    while (attempts_to_move_rooms_closer --) {
        center_room_layout();
CON("%d", attempts_to_move_rooms_closer);

        for (unsigned int rs = 0;
             rs < (unsigned int) all_placed_rooms.size();
             rs++) {

            std::fill(cells.begin(), cells.end(), Charmap::SPACE);

            //
            // which rooms shall we move?
            //
            for (auto x = 0; x < nodes->grid_width; x++) {
                for (auto y = 0; y < nodes->grid_height; y++) {
                    auto n = nodes->getn(x, y);
                    if (n->depth <= 0 ) {
                        continue;
                    }

                    auto r = get(grid.node_rooms, x, y);
                    if (r) {
                        r->skip = (random_range(0, 100) < 50);
                    }
                }
            }

            //
            // Place all rooms that are not going to move
            //
            for (auto x = 0; x < nodes->grid_width; x++) {
                for (auto y = 0; y < nodes->grid_height; y++) {
                    auto n = nodes->getn(x, y);
                    if (n->depth <= 0 ) {
                        continue;
                    }

                    auto r = get(grid.node_rooms, x, y);
                    if (!r) {
                        continue;
                    }
                    if (!r->skip) {
                        place_room(r, r->at.x, r->at.y);
                    }
                }
            }

            //
            // Place the rooms we want to move
            //
            auto moved = false;
            for (auto x = 0; x < nodes->grid_width; x++) {
                for (auto y = 0; y < nodes->grid_height; y++) {
                    auto n = nodes->getn(x, y);
                    if (n->depth <= 0 ) {
                        continue;
                    }

                    auto r = get(grid.node_rooms, x, y);
                    if (!r) {
                        continue;
                    }
                    if (!r->skip) {
                        continue;
                    }

                    delta = 1 + random_range(0, 3);

                    auto moved_one = false;
                    switch (random_range(0, 4)) {
                    case 0:
                        if (can_place_room(r, r->at.x - delta, r->at.y)) {
                            r->at.x -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x + delta, r->at.y)) {
                            r->at.x += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x, r->at.y - delta)) {
                            r->at.y -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x, r->at.y + delta)) {
                            r->at.y += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        break;

                    case 1:
                        if (can_place_room(r, r->at.x + delta, r->at.y)) {
                            r->at.x += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x - delta, r->at.y)) {
                            r->at.x -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x, r->at.y + delta)) {
                            r->at.y += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x, r->at.y - delta)) {
                            r->at.y -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        break;

                    case 2:
                        if (can_place_room(r, r->at.x, r->at.y - delta)) {
                            r->at.y -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x - delta, r->at.y)) {
                            r->at.x -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x + delta, r->at.y)) {
                            r->at.x += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x, r->at.y + delta)) {
                            r->at.y += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        break;

                    case 3:
                        if (can_place_room(r, r->at.x, r->at.y + delta)) {
                            r->at.y += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x, r->at.y - delta)) {
                            r->at.y -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x - delta, r->at.y)) {
                            r->at.x -= delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        if (can_place_room(r, r->at.x + delta, r->at.y)) {
                            r->at.x += delta;
                            place_room(r, r->at.x, r->at.y);
                            moved_one = true;
                            break;
                        }
                        break;
                    case 4:
                        ERR("wtf");
                    }

                    if (moved_one) {
                        moved = true;
                    } else {
                        place_room(r, r->at.x, r->at.y);
                    }
                }
            }

            if (!moved) {
                continue;
            }

            //
            // Ok we've moved one room. If we can still place corridors
            // then we can keep going. If not, rollback the room to the
            // last that was solvable.
            //
            std::vector<char> cells_ok;
            std::copy(mbegin(cells), mend(cells), mbegin(cells_ok));

            auto new_corridor_count = draw_corridors();
            if (new_corridor_count >= corridor_count) {
                restore_level();
                if (!draw_corridors()) {
                    ERR("rolled back level was not solvable");
                }

#if 0
                if (failed_to_make_shorter_corridors ++ > 1000) {
                    _ debug("failed to place shorter corridor layout");
                    return (true);
                }
#endif

                restore_level();
            } else if (!new_corridor_count) {
                restore_level();
                if (!draw_corridors()) {
                    ERR("rolled back level was not solvable");
                }

#if 0
                if (failed_to_place_all_corridors ++ > 1000) {
                    _ debug("failed to place shorter corridor layout");
                    return (true);
                }
#endif

                restore_level();
            } else {
CON("new_corridor_count %d", new_corridor_count);
                corridor_count = new_corridor_count;
                _ debug("success, placed corridors");
                failed_to_place_all_corridors = 0;
                failed_to_make_shorter_corridors = 0;
                std::copy(mbegin(cells_ok), mend(cells_ok), mbegin(cells));
                save_level();
            }
        }
    }
    _ debug("success, placed shorter corridor layout");

    return (draw_corridors());
}

void Dungeon::assign_rooms_to_tiles (void)
{
    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);
            if (r) {
                auto n = nodes->getn(x, y);
                r->depth = n->depth;
                map_place_room_ptr(r, r->at.x, r->at.y);
            }
        }
    }
}

void Dungeon::block_secret_doors (void)
{
    for (auto x = 0; x < map_width; x++) {
        for (auto y = 0; y < map_height; y++) {
            if (getc(x, y, MAP_DEPTH_WALLS) == Charmap::DOOR) {
                for (auto dy = -1; dy <= 1; dy++) {
                    for (auto dx = -1; dx <= 1; dx++) {
                        if (getc(x + dx, y + dy, MAP_DEPTH_FLOOR) == Charmap::SECRET_CORRIDOR) {
                            putc(x, y, MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                            goto next;
                        }
                    }
                }
            }
next: ;
        }
    }
}

void Dungeon::remove_all_doors (void)
{
    for (auto x = 0; x < map_width; x++) {
        for (auto y = 0; y < map_height; y++) {
            if (getc(x, y, MAP_DEPTH_WALLS) == Charmap::DOOR) {
                putc(x, y, MAP_DEPTH_WALLS, Charmap::SPACE);
            }
        }
    }
}

void Dungeon::place_doors_between_depth_changes (void)
{
    for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
            auto n = nodes->getn(x, y);
            if (n->depth <= 0 ) {
                continue;
            }

            auto r = get(grid.node_rooms, x, y);
            if (!r) {
                continue;
            }

            if (r->down_room) {
                auto o = r->down_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                if (r->depth > o->depth) {
                    putc(r->down_door_at.x, r->down_door_at.y,
                         MAP_DEPTH_WALLS, Charmap::DOOR);
                }
            }

            if (r->up_room) {
                auto o = r->up_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                if (r->depth > o->depth) {
                    putc(r->up_door_at.x, r->up_door_at.y,
                         MAP_DEPTH_WALLS, Charmap::DOOR);
                }
            }

            if (r->right_room) {
                auto o = r->right_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                if (r->depth > o->depth) {
                    putc(r->right_door_at.x, r->right_door_at.y,
                         MAP_DEPTH_WALLS, Charmap::DOOR);
                }
            }

            if (r->left_room) {
                auto o = r->left_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                if (r->depth > o->depth) {
                    putc(r->left_door_at.x, r->left_door_at.y,
                         MAP_DEPTH_WALLS, Charmap::DOOR);
                }
            }

            if (r->secret_down_room) {
                auto o = r->secret_down_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                putc(r->down_secret_door_at.x, r->down_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                putc(o->up_secret_door_at.x, o->up_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
            }

            if (r->secret_up_room) {
                auto o = r->secret_up_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                putc(r->up_secret_door_at.x, r->up_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                putc(o->down_secret_door_at.x, o->down_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
            }

            if (r->secret_right_room) {
                auto o = r->secret_right_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                putc(r->right_secret_door_at.x, r->right_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                putc(o->left_secret_door_at.x, o->left_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
            }

            if (r->secret_left_room) {
                auto o = r->secret_left_room;
                if (!o) {
                    ERR("room linkage bug");
                }

                putc(r->left_secret_door_at.x, r->left_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                putc(o->right_secret_door_at.x, o->right_secret_door_at.y,
                     MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
            }
        }
    }
}

void Dungeon::dmap_set_walls (Dmap *d)
{
    int x, y;

    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {

            if (is_anything_at(x, y)) {
                set(d->val, x, y, DMAP_IS_WALL);
            } else {
                set(d->val, x, y, DMAP_IS_PASSABLE);
            }
        }
    }
}

/*
Cellular Automata Method for Generating Random Cave-Like PlacedLevels


    From RogueBasin

Jump to: navigation < #column-one>, search < #searchInput>

By Jim Babcock < /index.php?title=Jim_Babcock&action=edit>

It is an old and fairly well documented trick to use cellular automata
< /index.php?title=Cellular_automata > to generate cave-like structures.
The basic idea is to fill the map randomly, then repeatedly apply the
4-5 rule: a tile is a wall if it is a wall and has 4 neighbors that are
walls, or if it is not a wall and has 5 neighbors that are. This rule
can be stated more simply: a tile becomes or remains a wall if the 3x3
region centered on it contains at least 5 walls. (/Note: It is important
to do this for each tile simultaneously. If you update one, then use its
value when you update the next, your results won't look as good, and the
tricks described later won't work./)

If the map initially contains 45% walls, and the process above is
repeated 5 times, the output looks like (for example)

############################################################
###....####################################.....############
##......######################..#########.........##########
##......#####################....#######...........####.####
##......###################.........................##...###
##......##################..........................###...##
#........##############.............................###...##
#........#############...............................#....##
##.......##############..................................###
##.......###..############..............................####
##.......##....############.............................####
#..............############...###........................###
#...............###########..#####...............##.......##
#................#################...............##.......##
##.....#####..........###########....#..........###.......##
##....#######...........########....###.........####......##
##....#######............######....####........#####......##
##....#######.............####....#####.......#####......###
#......######..............###....####........####......####
#.......######.............###...####.........###.......####
#........#####.............###..####.....................###
##........####..............#...####.....................###
#####......##...................####.....................###
######...........................##.....................####
######..................................................####
######.........###.....................####.............####
######......#########.................######............####
#######....#############.......##############.....###..#####
##############################################..############
############################################################

The problem is, the results of the algorithm are very inconsistent. Not
only is it prone to generating disjoint (not connected) maps, like in
this example, with the same parameters:

############################################################
#####################################################..#####
#####.....##################...###############............##
#####......###########.####....########.#####..............#
#####.......#########..###.....###############.............#
####.............#####.###....###################.........##
###...............########...####################........###
##.................#######...####################........###
##.......##.........#####.....##################.........###
##......####.........###.......################...........##
##.....########.................#######..######...........##
##...###########................######...#######..........##
#########..######..............######....########........###
########....######..#####......#####.....##########......###
#######......#############.....#####.....###########.....###
#######.......############......###.......###########.....##
#######.......###########.......###.......###########.....##
######.......####..######.......####.......#########......##
#####.......####....#####.......####..........######.....###
####........####......####......####...........#####.....###
####.........###.......###......####...##......######.....##
####...##.....###.......#......###########.....#######.....#
#####.####.....#####...........############....########....#
##########.....######..........############....#########..##
#########.......#####...........##########.....#############
#########.......####...............#####........############
##########......####................###...........##########
###########....#####.....######.....####...........#########
################################...##########.....##########
############################################################

it also sometimes generates maps which consist of basically one huge
open space, like this one:

############################################################
############################################################
#################.####.######..######........###############
########...#####...##...####....####..........######...#####
###.####...####....###..####....####..........#####.....####
##...###....##.....###...##.....###............###......####
###.####...........###..........###.....###.........########
########...........###...........#.......#.........#########
#######.............#..............................#########
######.....##..........................................#####
###.......###...........................................####
##.......####...........................................####
##......................................................####
##.....................................................#####
##.....................................................#####
#.....................................##...............#####
#.....................................##................####
#...........................###......###................####
##...........###............###.....#####...............####
###...........#..............##.....######............######
######.......................##......######........#########
##########..................##.........#####......##########
###########................###..........####......##########
############................#...........####......##########
###.....#####.........##...............#####.......####..###
###.....#####.......#####.............#####..............###
###.....####.......#####..............#####.....##.......###
####...#####.......#####.....#####...######....####.....####
#############.##########....################..##############
############################################################

We can fix the disjoint segments problem in one of three ways. Either
throw away maps that have disjoint segments in them, connect up the
segments after the fact, or fill in all but the biggest segment. We
can't just retry when we get a disjoint map, because if the map is big
then, statistically, that will be almost 100% of the time. Filling in
all but the biggest segment will tend to produce a small area in a map
that was supposed to be big. Connecting up the regions works, but it
tends to look unnatural, as in the example from above, now connected:

############################################################
#####################################################..#####
#####.....##################...###############............##
#####......###########.####....########....................#
#####.......#########..###.....###############.............#
####.............####..###....###################.........##
###...............###.####...####################........###
##.................##.####...####################........###
##.......##.........#.###.....##################.........###
##......####..........##.......################...........##
##.....########.................#######..######...........##
##...###########................######...#######..........##
#########..######..............######....########........###
########............#####......#####.....##########......###
#######......#############...............###########.....###
#######.......############......###.......###########.....##
#######.......###########.......###.......###########.....##
######.......####..######.......####.......#########......##
#####.......####....#####.......####.....................###
####........####......####......####...........#####.....###
####.........###.......###......####...##......######.....##
####...##.....###.......#......###########.....#######.....#
#####.####.....#####...........############....########....#
##########.....######..........############....#########..##
#########.......#####...........##########.....#############
#########.......####...............#####........############
##########......####................###...........##########
###########....#####.....######.....####...........#########
################################...##########.....##########
############################################################

The solution to both problems, as it turns out, is to revisit the
original cellular automata rules. Recall that the original rule was

   // There is a wall initially at P with 45% probability
   // In the next generation, there is a wall at spot P if the number of
    tiles around P which are walls is at least 5

Or, in more compact notation:

   // Winit (p) = rand[0,100) <  45
   // R (p) = the number of tiles within 1 step of p which are walls
   // W? (p) = R (p) ? 5

Now, one of the problems was that we tend to get big, open areas. So why
not try filling those areas in? Change the rule to

   // W? (p) = R (p) ? 5 or p is in the middle of an open space

Or more formally,

   // Rn (p) = the number of tiles within n steps of p which are walls
   // W? (p) = R1 (p)?5 || R2 (p)=0

So how does it look?

Winit (p) = rand[0,100) <  45
Repeat 5: W? (p) = R1 (p) ? 5 || R2 (p) ? 1

############################################################
##....######################################################
#.......###..#####..####....###########################..###
#...#.........###.............##########..############....##
##...###...#..###..............########....######..###....##
###...######...#..##...........######.....######....###..###
####..######......##..##........####...#..######....########
####..###.#.......#...##...#.....##...###..######...########
#####.........##...........##........####.....##.....#######
#####.........##...........#.......##.....#.............####
####...###...##................#...##......###...........###
####...###..##...###....##.....##..##..##..###....##.....###
#########..###..####...###.............###..##..####.....###
########...##..#####...##...............#...#...####....####
#######........######......###...##....................#####
#######..##.....######....##########...................#####
######..####.......####...#########...................######
####....####..##....##.....#######...##..............#######
###.....###..#####......#...####....##................######
##..##..###..###........##.........#....#......##......#####
#..####..##...##.................###...##.....####......####
#.....#..###..#..##..........#..###..###.....#####......####
##.......####.....#...##........##..###....#######......####
######....###.......................###...#######....#######
#######......................##.....###...#######...########
########.................#######....####...#####....########
########..............###########..######...........########
#########....####....######################........#########
###################.########################################
############################################################

This is more interesting - it doesn't have any big open areas, it has a
decent layout. It's almost fully connected. Still, it has some new
problems: there are isolated single-tile walls in places, and in general
it's not very smooth. But with a little tweaking:

Winit (p) = rand[0,100) <  40
Repeat 4: W? (p) = R1 (p) ? 5 || R2 (p) ? 2
Repeat 3: W? (p) = R1 (p) ? 5

############################################################
###...###########..#############################.....#######
##..........####....################..#########.........####
##...........##.....####..#########.......####..######...###
##.......#..........###....###.................########..###
##......###........###........................#########..###
##.......##.........#........................##########...##
##.......###...........##.............###....#########.....#
##.......######.......####...........#####....#####........#
###.....#########....#####...........######...#####........#
###########################...........#####...#######.....##
#############...###########.............##....########....##
############.........#######...................#######....##
###########...........########......###............##....###
###..#####.............#########...##########............###
##....###...............######################..........####
###..........................######..#########..........####
####..........................###.....#######...........####
####.................##................##................###
####...###..........####...............#..................##
###...#####.........####..............##......##...........#
##....########......#####............####....####..........#
##....#########.....#####............####....####..........#
##.....######.......#####.............##.....####...##.....#
##......##..........#####....................####..####....#
###.................####.........###........############..##
###............##..######.###...############################
####..........##############################################
######..####################################################
############################################################

Notice that the initial fill percentage is a little lower, the cutoffs
are different, and we switch rules after a few generations. This is more
like the desired result. So, with these parameters, I give you some more
samples, at various sizes.

##############################
##..###....###.....###########
#...........................##
#.................##.........#
##..###..........#######.....#
########.........#######.....#
############......####......##
#############...............##
###..########...............##
##....#######...###..#......##
##.....######...#######.....##
##......#####...######......##
##...#...###....#####.......##
##..##.........######.......##
##..........##########......##
###........#####..####.....###
###........####....###.....###
###....##...##.....###.....###
###...####........####......##
###...#####......#####......##
##....#####.....#####.......##
##.....###.....####.........##
##..............##..........##
###.........................##
####........................##
####.......................###
####..........##...........###
#####...###..####.........####
####################.....#####
##############################

############################################################
#########......###...##........####...####.....#############
####............................##.....##............#######
###................###.....##..........................#####
###...............#####...####..........................####
###...............#####....####............#............####
####...###.........####.......##.......................#####
##########..........###........##.....................######
##########...........#..........##...................#######
#########.......................#####..............#########
######.........................#######...#......############
#####..........................############....#############
####...........................###########......######..####
###..........##.................#########................###
##.......#######........#..........######...###.........####
##......########.......##............###...######.....######
###.....#######...............#####........########..#######
###......#####...##...........######........################
###......#####..####...........#####.........###############
#######..#####..####............###...........#######....###
########..###...#####......###.................#####......##
########.......######......####.................###.......##
########.......######.......##....##..................##..##
#######.......######....##.......####................####..#
######.......#######....###......####..........###..#####..#
#####........######.....######....##..........##########...#
######........###........######...............########.....#
##########...............#######.............########.....##
#############...#######..###########...#####################
############################################################

################################################################
#######..#####............####..####...###....###########...####
###......####..................................#########.....###
##.......###.......................................####......###
##......####.............##.........................##......####
##......#####......##...####................##..............####
##......##############..#####...............###.............####
##.....###############...#####...............##........##...####
##.....################..######.........#.............####...###
##.....################...#####........###............####....##
###.....#####..##...##....####.........###.............###....##
####....####..............###..........###...................###
####....####.............####..........##....................###
###.....####...........#####.........................##.....####
##.......##............#####....................##..####...#####
##.....................######................###########...#####
###..##........##......###############.....############....#####
########......####....#################..###############..######
#########...####################################################
################################################################

############################################################
#########......###...##........####...####.....#############
####............................##.....##............#######
###................###.....##..........................#####
###...............#####...####..........................####
###...............#####....####............#............####
####...###.........####.......##.......................#####
##########..........###........##.....................######
##########...........#..........##...................#######
#########.......................#####..............#########
######.........................#######...#......############
#####..........................############....#############
####...........................###########......######..####
###..........##.................#########................###
##.......#######........#..........######...###.........####
##......########.......##............###...######.....######
###.....#######...............#####........########..#######
###......#####...##...........######........################
###......#####..####...........#####.........###############
#######..#####..####............###...........#######....###
########..###...#####......###.................#####......##
########.......######......####.................###.......##
########.......######.......##....##..................##..##
#######.......######....##.......####.........##.....####..#
#####........#######....###......####........#####..#####..#
####........#######.....######...#####.......############..#
####.......######..........####..#########..#############..#
###........#####............###..########################.##
##.........####.............###..################.######..##
#....###...####......####....#...######..#######...#####..##
#.....#.....##......######.......#####....#####....#####..##
#...................######........####....###.....#####...##
#....................#####........#####..###......##......##
#....................######........########................#
##......#............########.......#######................#
##......##...........#########......#######...............##
###.....#............####...##.....#######..##...........###
###..........#......####...........######..####..........###
##..........####....####...........#####..######.........###
##...........####..#####............##....######.........###
##............###..######......#...........####..........###
##............###..#######.....##........................###
##.......###...#....#######....#..........................##
###......###.........######.........................##.....#
###.......#..........######........#####...........####....#
###............###...######......########.........#####....#
###...........#####..######.....#########.........####.....#
###...........#####.#######.....########...........###.....#
###...........####..########...#########......##...###....##
###...........####...##################......####..###....##
###...........####......##############.......####..###....##
###...........####..........##########........##...###....##
###............####..........#########.............####..###
###...........#####...........#######..............#########
###.....##########............######.......##......#########
##.....###########.....###.....####.......####......########
##.....############....###......##.......#####........######
###...##############..#####.............#######.......######
################################...##..#####################
############################################################

There's still no guarantee of connectedness, though. However, it's now
consistently almost-connected, so that you can reasonably just drop the
isolated chunks.

Finally, here is the C program I used to try out different parameters.
Before putting this into an actual game, handling of disconnected
regions is needed.

*/

//
// Grow our cells
//
void Dungeon::cave_generation (void)
{
    const int16_t maze_w = MAP_WIDTH - 2;
    const int16_t maze_h = MAP_HEIGHT - 2;
    int16_t x, y;

    for (x=2; x < maze_w; x++) {
        for (y=2; y < maze_h; y++) {

            uint8_t adjcount = 0;

#define ADJ(i,j) adjcount += get(map_curr, x+i, y+j);

            ADJ(-1,-1);
            ADJ(-1, 0);
            ADJ(-1, 1);

            ADJ( 0,-1);
            ADJ( 0, 0);
            ADJ( 0, 1);

            ADJ( 1,-1);
            ADJ( 1, 0);
            ADJ( 1, 1);

            if (adjcount >= MAP_R1) {
                continue;
            }

            ADJ( -2,-1);
            ADJ( -2, 0);
            ADJ( -2, 1);

            ADJ( -1,-2);
            ADJ( -1, 2);

            ADJ(  0,-2);
            ADJ(  0, 2);

            ADJ(  1,-2);
            ADJ(  1, 2);

            ADJ(  2,-1);
            ADJ(  2, 0);
            ADJ(  2, 1);

            //
            // Adjust for the grow threshold for rock or flow.
            //
            if (adjcount <= MAP_R2) {
                //
                // map_save set to 0 already.
                //
            } else {
                set(map_save, x, y, (uint8_t)1);
            }
        }
    }
}

//
// Any water next to cave walls make it shallow
//
void Dungeon::water_fixup_shallows (void)
{
    for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
        for (auto x = 1; x < MAP_WIDTH - 1; x++) {
            if (!is_deep_water_fast(x, y)) {
                continue;
            }

            if (is_wall(x - 1, y - 1) ||
                is_wall(x    , y - 1) ||
                is_wall(x + 1, y - 1) ||
                is_wall(x - 1, y    ) ||
                is_wall(x    , y    ) ||
                is_wall(x + 1, y    ) ||
                is_wall(x - 1, y + 1) ||
                is_wall(x    , y + 1) ||
                is_wall(x + 1, y + 1) ||
                is_rock(x - 1, y - 1) ||
                is_rock(x    , y - 1) ||
                is_rock(x + 1, y - 1) ||
                is_rock(x - 1, y    ) ||
                is_rock(x    , y    ) ||
                is_rock(x + 1, y    ) ||
                is_rock(x - 1, y + 1) ||
                is_rock(x    , y + 1) ||
                is_rock(x + 1, y + 1)) {
                putc(x, y, MAP_DEPTH_WATER, Charmap::WATER);
            }
        }
    }
}

//
// Add deepwater and islands of safety.
//
void Dungeon::water_fixup (void)
{
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> cand {};

    for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
        for (auto x = 1; x < MAP_WIDTH - 1; x++) {
            if (is_water(x - 1, y - 1) &&
                is_water(x    , y - 1) &&
                is_water(x + 1, y - 1) &&
                is_water(x - 1, y    ) &&
                is_water(x    , y    ) &&
                is_water(x + 1, y    ) &&
                is_water(x - 1, y + 1) &&
                is_water(x    , y + 1) &&
                is_water(x + 1, y + 1)) {
                set(cand, x, y, true);
            }
        }
    }
    for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
        for (auto x = 1; x < MAP_WIDTH - 1; x++) {
            if (get(cand, x, y)) {
                if (random_range(0, 100) < 95) {
                    putc(x, y, MAP_DEPTH_WATER, Charmap::DEEP_WATER);
                } else {
                    putc(x, y, MAP_DEPTH_WATER, Charmap::SPACE);
                    putc(x, y, MAP_DEPTH_FLOOR, Charmap::DIRT);
                }
            }
        }
    }
}

void Dungeon::add_remaining (void)
{
    for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
        for (auto x = 1; x < MAP_WIDTH - 1; x++) {
            if (is_anything_at(x, y)) {
                continue;
            }

            if (random_range(0, 100) < 95) {
                putc(x, y, MAP_DEPTH_WALLS, Charmap::ROCK);
            }
            putc(x, y, MAP_DEPTH_WATER, Charmap::SPACE);
            putc(x, y, MAP_DEPTH_FLOOR, Charmap::DIRT);
        }
    }
}

//
// Generate a cave!
//
void Dungeon::cave_gen (uint8_t map_fill_prob,
                        uint8_t map_r1,
                        uint8_t map_r2,
                        uint8_t map_generations)

{
    map_save = {};
    map_curr = {};

    const int16_t maze_w = MAP_WIDTH - 2;
    const int16_t maze_h = MAP_HEIGHT - 2;

    if (map_fill_prob) {
        MAP_FILL_PROB             = map_fill_prob;
    }

    if (map_r1) {
        MAP_R1                    = map_r1;
    }

    if (map_r2) {
        MAP_R2                    = map_r2;
    }

    if (map_generations) {
        MAP_GENERATIONS           = map_generations;
    }

    int16_t x, y, i;

    map_curr = {};

    for (x=2; x < maze_w-2; x++) {
        for (y=2; y < maze_h-2; y++) {
            if ((myrand() % 100) < MAP_FILL_PROB) {
                set(map_curr, x, y, (uint8_t)1);
            }
        }
    }

    for (i=0; i < MAP_GENERATIONS; i++) {
        cave_generation();
        std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
        map_save = {};
    }

    for (x=2; x < maze_w-2; x++) {
        for (y=2; y < maze_h-2; y++) {
            if (get(map_curr, x, y)) {
                if (!is_anything_at(x, y)) {
                    putc(x, y, MAP_DEPTH_WALLS, Charmap::ROCK);
                }
            }
        }
    }
}

void Dungeon::dirt_gen (uint8_t map_fill_prob,
                        uint8_t map_r1,
                        uint8_t map_r2,
                        uint8_t map_generations)

{
    map_save = {};
    map_curr = {};

    const int16_t maze_w = MAP_WIDTH - 2;
    const int16_t maze_h = MAP_HEIGHT - 2;

    if (map_fill_prob) {
        MAP_FILL_PROB             = map_fill_prob;
    }

    if (map_r1) {
        MAP_R1                    = map_r1;
    }

    if (map_r2) {
        MAP_R2                    = map_r2;
    }

    if (map_generations) {
        MAP_GENERATIONS           = map_generations;
    }

    int16_t x, y, i;

    map_curr = {};

    for (x=2; x < maze_w-2; x++) {
        for (y=2; y < maze_h-2; y++) {
            if ((myrand() % 100) < MAP_FILL_PROB) {
                set(map_curr, x, y, (uint8_t)1);
            }
        }
    }

    for (i=0; i < MAP_GENERATIONS; i++) {
        cave_generation();
        std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
        map_save = {};
    }

    for (x=2; x < maze_w-2; x++) {
        for (y=2; y < maze_h-2; y++) {
            if (get(map_curr, x, y)) {
                if (!is_anything_at(x, y)) {
                    putc(x, y, MAP_DEPTH_FLOOR, Charmap::DIRT);
                }
            }
        }
    }
}

void Dungeon::water_gen (uint8_t map_fill_prob,
                         uint8_t map_r1,
                         uint8_t map_r2,
                         uint8_t map_generations)
{
    map_save = {};
    map_curr = {};

    const int16_t maze_w = MAP_WIDTH - 2;
    const int16_t maze_h = MAP_HEIGHT - 2;

    if (map_fill_prob) {
        MAP_FILL_PROB             = map_fill_prob;
    }

    if (map_r1) {
        MAP_R1                    = map_r1;
    }

    if (map_r2) {
        MAP_R2                    = map_r2;
    }

    if (map_generations) {
        MAP_GENERATIONS           = map_generations;
    }

    int16_t x, y, i;

    map_curr = {};

    for (x=2; x < maze_w-2; x++) {
        for (y=2; y < maze_h-2; y++) {
            if ((myrand() % 100) < MAP_FILL_PROB) {
                set(map_curr, x, y, (uint8_t)1);
            }
        }
    }

    for (i=0; i < MAP_GENERATIONS; i++) {

#if 0
        for (y=2; y < maze_h-2; y++) {
            for (x=2; x < maze_w-2; x++) {
                if (get(map_curr, x, y)) {
                    printf("W");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
printf("----------------------------------\n");
#endif

        cave_generation();
        std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
        map_save = {};
    }

    for (x=2; x < maze_w-2; x++) {
        for (y=2; y < maze_h-2; y++) {
            if (get(map_curr, x, y)) {
                if (!is_anything_at(x, y)) {
                    putc(x, y, MAP_DEPTH_WATER, Charmap::WATER);
                }
            }
        }
    }
}

Dungeonp dungeon_test (void)
{
#if 0
    auto x = 1000 ;
    while (x--) {
        //
        // smaller node numbers mean larger rooms
        //
        mysrand(x);
        new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH, GRID_HEIGHT, x);
    }

    return (nullptr);
#else
    int x = 663;
    mysrand(x);
    auto d = new Dungeon(MAP_WIDTH, MAP_HEIGHT, GRID_WIDTH, GRID_HEIGHT, x);

    return (d);
#endif
}
