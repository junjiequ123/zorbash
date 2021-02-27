//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_MONST_H_
#define _MY_MONST_H_

#include <list>
#include "my_time.h"
#include "my_light.h"
#include "my_thing_ai.h"
#include "my_thing_id.h"

constexpr uint32_t THING_MAGIC_BEGIN = 11221122;
constexpr uint32_t THING_MAGIC_END   = 22112211;
constexpr uint32_t THING_MAGIC_FINAL = 33333333;

enum {
    MONST_SIZE_TINY,
    MONST_SIZE_SMALL,
    MONST_SIZE_NORMAL,
    MONST_SIZE_LARGE,
    MONST_SIZE_GIANT,
    MONST_SIZE_GARGANTUAN,
};

typedef struct Monst_ {
public:
    AgeMap       *_age_map = {};             // How old a cell is
    Dmap         *_dmap_scent = {};
    std::vector<Lightp> light = {};          // Has light sources?

    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    ThingId      on_fire_id_anim {};
    ThingId      owner_id {};                // Who carries this thing?
    ThingId      minion_owner_id {};              // Who created this thing?
    ThingId      weapon_id {};               // Current weapon
    ThingId      weapon_id_carry_anim {};
    ThingId      weapon_id_use_anim {};
    color        light_col {};
    float        bounce_fade = {};           // 0.1; rapid, 0.9 slow
    float        bounce_height = {};         // Percentage of tile height.
    float        fadeup_fade = {};           // 0.1; rapid, 0.9 slow
    float        fadeup_height = {};         // Percentage of tile height.
    float        fall_height = {};           // y offset for falling
    float        wobble = {};                // Fades when set
    fpoint       lunge_to;                   // When a monst attacks something
    int          bag_height {};
    int          bag_width {};
    int          bounce_count = {};
    int          gold = {};
    int          health = {};
    int          health_max = {};
    int          keys = {};
    int          lifespan = {};              // How many things this thing owns.
    int          light_quality {};
    int          light_strength {};
    int          modifier_attack = {};
    int          modifier_constitution = {};
    int          modifier_defence = {};
    int          modifier_strength = {};
    int          owned_count = {};           // How many things this thing owns.
    int          minion_count = {};          // How many things this thing spawned.
    int          stamina = {};
    int          stamina_max = {};
    int          poison = {};
    int          stats01 = {};
    int          stats02 = {};
    int          stats03 = {};
    int          stats04 = {};
    int          stats05 = {};
    int          stats06 = {};
    int          stats07 = {};
    int          stats08 = {};
    int          stats09 = {};
    int          stats10 = {};
    int          stats11 = {};
    int          stats12 = {};
    int          stats17 = {};
    int          stats_stats19 = {};
    int          submerged_offset = {};      // GL co-orids
    int          throw_distance = {};
    int          tick_rate_tenths = {};
    int          tick_resurrect_when = {};
    point        bag_position{-1, -1};
    point        wander_target{-1, -1};
    point        where_i_dropped_an_item_last{-1, -1};
    point        where_i_failed_to_collect_last{-1, -1};
    std::array<std::array<ThingId, MAX_BAG_WIDTH>, MAX_BAG_HEIGHT> bag {};
    std::list<ThingId>    carrying;
    std::list<ThingId>    skills;
    std::string           msg;               // Text that floats on screen
    std::vector<ThingId>  enemies;           // List of things that wronged us
    std::vector<point>    move_path;
    std::vector<uint16_t> inventory_id;      // Vector of tp_id
    std::vector<uint16_t> skillbox_id;       // Vector of tp_id
    timestamp_t  timestamp_born {};
    timestamp_t  timestamp_bounce_begin {};
    timestamp_t  timestamp_bounce_end {};
    timestamp_t  timestamp_fadeup_begin {};
    timestamp_t  timestamp_fadeup_end {};
    timestamp_t  timestamp_fall_begin {};
    timestamp_t  timestamp_fall_end {};
    timestamp_t  timestamp_flip_start {};    // Used for animating the steps.
    timestamp_t  timestamp_hunger_tick {};   // Ticks every time does something. Used from memory aging
    timestamp_t  timestamp_jump_begin {};
    timestamp_t  timestamp_jump_end {};
    timestamp_t  timestamp_last_tick {};
    timestamp_t  timestamp_last_ticked {};
    timestamp_t  timestamp_last_wander_try {};
    timestamp_t  timestamp_lunge_begin {};
    timestamp_t  timestamp_lunge_end {};
    timestamp_t  timestamp_move_begin {};
    timestamp_t  timestamp_move_end {};
    timestamp_t  timestamp_sleep_end {};
    uint32_t     tick = {};                  // Increments on completion of move
    uint32_t     tick_last_did_something {};
    uint32_t     tick_last_escape {};
    uint32_t     tick_last_level_change {};
    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////
 
    //
    // Things not worth saving
    //
    point        preferred_bag_position{-1, -1};
} Monst;
std::ostream& operator<<(std::ostream &out, Bits<const Monstp & > const my);
std::istream& operator>>(std::istream &in, Bits<Monstp &> my);

#endif // _MY_THING_H_