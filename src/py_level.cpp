//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_depth.h"
#include "my_python.h"
#include "my_level_static.h"

PyObject *map_load_level_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *level_name = 0;
    PyObject *py_level_data = 0;

    static char *kwlist[] = {
        (char*) "level_data",
        (char*) "level_name",
        0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds,
                                     "|Os",
                                     kwlist,
                                     &py_level_data,
                                     &level_name)) {
        Py_RETURN_NONE;
    }

    if (!py_level_data) {
        ERR("map_load_level, missing floor data");
    }

    int level_data_elems = PyList_Size(py_level_data);
    if (level_data_elems % MAP_HEIGHT) {
        ERR("level elems needs to be evenly dividable by level height %d, got %d elems when loading %s",
            (int) MAP_HEIGHT, (int) PyList_Size(py_level_data), level_name);
    }

    auto l = LevelStatic::level_new();
    for (auto n=0; n < MAP_WIDTH; n++) {
        for (auto y=0; y<MAP_HEIGHT; y++) {
            auto o = PyList_GetItem(py_level_data, y); /* Can't fail */
            if (!o) {
                continue;
            }

            std::string floor_string;
            std::string water_string;
            std::string lava_string;
            std::string chasm_string;
            std::string walls_string;
            std::string obj_strings;

            for (auto& c : py_obj_to_string(o)) {
                auto m = get(Charmap::all_charmaps, c);

                if (m.is_floor ||
                    m.is_secret_corridor ||
                    m.is_dirt) {
                    floor_string += c;
                } else if (m.is_blood        ||
                           m.is_deep_water   ||
                           m.is_door         ||
                           m.is_entrance     ||
                           m.is_exit         ||
                           m.is_floor_deco   ||
                           m.is_food         ||
                           m.is_generator    ||
                           m.is_gold         ||
                           m.is_key          ||
                           m.is_lava         ||
                           m.is_monst        ||
                           m.is_item_class_a ||
                           m.is_item_class_b ||
                           m.is_potion       ||
                           m.is_secret_door  ||
                           m.is_torch        ||
                           m.is_trap         ||
                           m.is_treasure     ||
                           m.is_water        ||
                           m.is_floor_deco) {
                    floor_string += Charmap::FLOOR;
                } else {
                    floor_string += Charmap::SPACE;
                }

                if (m.is_water ||
                    m.is_deep_water) {
                    water_string += c;
                } else {
                    water_string += Charmap::SPACE;
                }

                if (m.is_lava) {
                    lava_string += c;
                } else {
                    lava_string += Charmap::SPACE;
                }

                if (m.is_chasm) {
                    chasm_string += c;
                } else {
                    chasm_string += Charmap::SPACE;
                }

                if (m.is_wall ||
                    m.is_secret_door ||
                    m.is_door) {
                    walls_string += c;
                } else if (m.is_wall_deco) {
                    walls_string += Charmap::WALL;
                } else {
                    walls_string += Charmap::SPACE;
                }

                if (m.is_blood        ||
                    m.is_entrance     ||
                    m.is_exit         ||
                    m.is_floor_deco   ||
                    m.is_food         ||
                    m.is_generator    ||
                    m.is_gold         ||
                    m.is_key          ||
                    m.is_monst        ||
                    m.is_item_class_a ||
                    m.is_item_class_b ||
                    m.is_potion       ||
                    m.is_torch        ||
                    m.is_trap         ||
                    m.is_treasure     ||
                    m.is_wall_deco) {
                    obj_strings += c;
                } else {
                    obj_strings += Charmap::SPACE;
                }
            }

            if (floor_string.size() != MAP_WIDTH){
                ERR("level floor width mismatch, %d, expected %d",
                    (int)floor_string.size(), MAP_WIDTH);
            }
            if (water_string.size() != MAP_WIDTH){
                ERR("level water width mismatch, %d, expected %d",
                    (int)water_string.size(), MAP_WIDTH);
            }
            if (lava_string.size() != MAP_WIDTH){
                ERR("level lava width mismatch, %d, expected %d",
                    (int)lava_string.size(), MAP_WIDTH);
            }
            if (chasm_string.size() != MAP_WIDTH){
                ERR("level chasm width mismatch, %d, expected %d",
                    (int)chasm_string.size(), MAP_WIDTH);
            }
            if (walls_string.size() != MAP_WIDTH){
                ERR("level walls width mismatch, %d, expected %d",
                    (int)walls_string.size(), MAP_WIDTH);
            }
            if (obj_strings.size() != MAP_WIDTH){
                ERR("level items width mismatch, %d, expected %d",
                    (int)obj_strings.size(), MAP_WIDTH);
            }

            for (auto x = 0; x < MAP_WIDTH; x++) {
                if (floor_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_FLOOR, floor_string[x]);
                }
                if (water_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_WATER, water_string[x]);
                }
                if (lava_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_LAVA,  lava_string[x]);
                }
                if (chasm_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_CHASM, chasm_string[x]);
                }
                if (walls_string[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_OBJ,  walls_string[x]);
                }
                if (obj_strings[x] != ' ') {
                    set(l->data, x, y, MAP_DEPTH_OBJ,  obj_strings[x]);
                }
            }

            if (floor_string.size() != MAP_WIDTH){
                ERR("level floor width mismatch, %d, expected %d",
                    (int)floor_string.size(), MAP_WIDTH);
            }
            if (water_string.size() != MAP_WIDTH){
                ERR("level water width mismatch, %d, expected %d",
                    (int)water_string.size(), MAP_WIDTH);
            }
            if (walls_string.size() != MAP_WIDTH){
                ERR("level walls width mismatch, %d, expected %d",
                    (int)walls_string.size(), MAP_WIDTH);
            }
            if (obj_strings.size() != MAP_WIDTH){
                ERR("level items width mismatch, %d, expected %d",
                    (int)obj_strings.size(), MAP_WIDTH);
            }

            for (auto x = 0; x < MAP_WIDTH; x++) {
                set(l->data, x, y, MAP_DEPTH_FLOOR, floor_string[x]);
                set(l->data, x, y, MAP_DEPTH_WATER, water_string[x]);
                set(l->data, x, y, MAP_DEPTH_LAVA,  lava_string[x]);
                set(l->data, x, y, MAP_DEPTH_CHASM, chasm_string[x]);
                set(l->data, x, y, MAP_DEPTH_OBJ,   walls_string[x]);
            }
        }
    }
    l->finalize();

    Py_RETURN_NONE;
}
