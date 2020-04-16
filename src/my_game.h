//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_GAME_H_
#define _MY_GAME_H_

#include "my_sdl.h"
#include "my_dmap.h"
#include <array>
#include <list>
#include <unordered_map>

struct Thing_;
class Light;

typedef class Light* Lightp;
typedef struct Thing_* Thingp;
typedef class World* Worldp;
typedef class Level* Levelp;

enum {
    MAP_DEPTH_FLOOR,
    MAP_DEPTH_HAZARD,
#define MAP_DEPTH_LAST_FLOOR_TYPE MAP_DEPTH_HAZARD
    MAP_DEPTH_WALLS,
    MAP_DEPTH_WALLS_DECO,
    MAP_DEPTH_FLOOR_DECO,
    MAP_DEPTH_EXIT,
#define MAP_DEPTH_FIRE MAP_DEPTH_EXIT
    MAP_DEPTH_ITEM,
    MAP_DEPTH_MONST,
    MAP_DEPTH_PLAYER,
    MAP_DEPTH_WEAPON,
    MAP_DEPTH_CURSOR,
    MAP_DEPTH,
};

class Level {
public:
    //
    // These are caches for fast lookup in display code
    //
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_corpse {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_gfx_large_shadow {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_hazard {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_secret_door {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_visited {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_water {};

    //
    // When this Level was made. Used to restore timestamps relative to this.
    //
    timestamp_t                timestamp_dungeon_created {};
    timestamp_t                timestamp_dungeon_saved {};

    //
    // Where we are in the world
    //
    point3d                    world_at;

    //
    // All randomness jumps off of this as the root
    //
    int                        seed {};

    //
    // Something moved on the map; update caches
    //
    bool                       map_changed {};

    bool                       cursor_needs_update = false;
    bool                       cursor_found = false;
    fpoint                     cursor_at;
    fpoint                     cursor_at_old;
    bool                       map_follow_player = true;
    fpoint                     map_at;        // map tile location
    fpoint                     map_wanted_at; // map scroll desired at
    point                      pixel_map_at;  // map pixel location
    point                      map_tl;        // visible map tl
    point                      map_br;        // visible map br
    bool                       minimap_valid = false;
    int                        mouse {-1};    // ticks for every move
    int                        mouse_old {-1};
    uint8_t                    next_thing_id {};

    Thingp                     player = {};
    Thingp                     cursor = {};

    //
    // All things. The array index is part of the thing ID
    //
    class Thing_entropy {
    public:
        Thingp   ptr {};
        uint32_t id {};
    };
    std::array<class Thing_entropy, MAX_THINGS> all_thing_ptrs {};

    std::map<uint32_t, Thingp> all_things {};
    std::map<uint32_t, Thingp> all_active_things {};
    std::map<uint32_t, Thingp> all_gc_things {};

    std::array<std::array<bool, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    water_tile_map = {};

    //
    // All thing IDs
    //
    std::array<
      std::array<
        std::array<uint32_t, MAP_SLOTS>, MAP_HEIGHT>, MAP_WIDTH>
          all_thing_ids_at {};

    std::array<
      std::array<
        std::vector<Thingp>, MAP_HEIGHT>, MAP_WIDTH>
          all_thing_ptrs_at {};

    Level (void)
    {_
        newptr(this, "level");
    }

    ~Level (void)
    {_
        oldptr(this);
    }

    void alloc_thing_id(Thingp t);
    void realloc_thing_id(Thingp t);
    void free_thing_id(Thingp t);
    Thingp test_thing_ptr(uint32_t id);
    Thingp find_thing_ptr(uint32_t id);

    void remove_thing(int x, int y, uint32_t id);
    void remove_thing(point p, uint32_t id);

    void put_thing(int x, int y, uint32_t id);
    void put_thing(point p, uint32_t id);

    #define JOIN1(X,Y) X##Y
    #define JOIN(X,Y) JOIN1(X,Y)

    #define FOR_ALL_THINGS(level, t, x, y)                          \
        if (!(level)->is_oob(x, y)) {                               \
            for (auto t : get(level->all_thing_ptrs_at, x, y)) {    \
                verify(t);                                          \

    #define FOR_ALL_THINGS_END() } }

    #define FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z)              \
        if (!(level)->is_oob(x, y)) {                               \
            for (auto t : get(level->all_thing_ptrs_at, x, y)) {    \
                verify(t);                                          \
                auto tpp = t->tp();                                 \
                if (tpp->z_depth != z) {                            \
                    continue;                                       \
                }

    #define FOR_ALL_THINGS_AT_DEPTH_END() } }

    void get_all_things_at_depth(int x, int y, int z, std::vector<Thingp> &);

    //
    // Things that move around and things that do not, but are interesting,
    // like food
    //
    #define FOR_ALL_INTERESTING_THINGS(level, t, x, y)                   \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);                 \
        level->get_all_interesting_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_interesting_things_at(int x, int y, std::vector<Thingp> &);

    //
    // Things that move around and things that do not, but are interesting,
    // like food
    //
    #define FOR_ALL_COLLISION_THINGS(level, t, x, y)                     \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);                 \
        level->get_all_collision_things_at(x, y, JOIN1(tmp, __LINE__));   \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_collision_things_at(int x, int y, std::vector<Thingp> &);

    //
    // Things that emit light
    //
    #define FOR_ALL_LIGHT_SOURCE_THINGS(level, t, x, y)                   \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);                  \
        level->get_all_light_source_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_light_source_things_at(int x, int y, std::vector<Thingp> &);

    //
    // Things that move around
    //
    #define FOR_ALL_ACTIVE_THINGS(level, t, x, y)                   \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);            \
        level->get_all_active_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_active_things_at(int x, int y, std::vector<Thingp> &);

    //
    // Things that block progress
    //
    #define FOR_ALL_OBSTACLE_THINGS(level, t, x, y)                   \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);              \
        level->get_all_obstacle_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_obstacle_things_at(int x, int y, std::vector<Thingp> &);

    //
    // Cursor path is the highlighted path the player follows.
    //
    #define FOR_ALL_CURSOR_PATH_THINGS(level, t, x, y)                   \
        static std::vector<Thingp> JOIN1(tmp, __LINE__);                 \
        level->get_all_cursor_path_things_at(x, y, JOIN1(tmp, __LINE__)); \
        for (auto t : JOIN1(tmp, __LINE__))
    void get_all_cursor_path_things_at(int x, int y, std::vector<Thingp> &);

    void display(void);
    void update_map(void);
    void update_minimap(void);

    void clear(void);
    bool is_anything_at(const int x, const int y);
    bool is_anything_at(const point &p);
    bool is_door(const int x, const int y);
    bool is_door(const point &p);
    bool is_food(const int x, const int y);
    bool is_food(const point &p);
    bool is_key(const int x, const int y);
    bool is_key(const point &p);
    bool is_monst(const int x, const int y);
    bool is_monst(const point &p);

    bool is_floor(const int x, const int y);
    bool is_floor(const point &p);
    void set_floor(const int x, const int y);
    void unset_floor(const int x, const int y);

    bool is_corridor(const int x, const int y);
    bool is_corridor(const point &p);
    void set_corridor(const int x, const int y);
    void unset_corridor(const int x, const int y);

    bool is_blood(const int x, const int y);
    bool is_blood(const point &p);
    void set_blood(const int x, const int y);
    void unset_blood(const int x, const int y);

    bool is_wall(const int x, const int y);
    bool is_wall(const point &p);
    void set_wall(const int x, const int y);
    void unset_wall(const int x, const int y);

    bool is_water(const int x, const int y);
    bool is_water(const point &p);
    void set_water(const int x, const int y);
    void unset_water(const int x, const int y);

    bool is_lava(const int x, const int y);
    bool is_lava(const point &p);
    void set_lava(const int x, const int y);
    void unset_lava(const int x, const int y);

    bool is_hazard(const int x, const int y);
    bool is_hazard(const point &p);
    void set_hazard(const int x, const int y);
    void unset_hazard(const int x, const int y);

    bool is_secret_door(const int x, const int y);
    bool is_secret_door(const point &p);
    void set_secret_door(const int x, const int y);
    void unset_secret_door(const int x, const int y);

    bool is_corpse(const int x, const int y);
    bool is_corpse(const point &p);
    void set_corpse(const int x, const int y);
    void unset_corpse(const int x, const int y);

    bool is_dirt(const int x, const int y);
    bool is_dirt(const point &p);
    void set_dirt(const int x, const int y);
    void unset_dirt(const int x, const int y);

    bool is_rock(const int x, const int y);
    bool is_rock(const point &p);
    void set_rock(const int x, const int y);
    void unset_rock(const int x, const int y);

    bool is_dungeon(const int x, const int y);
    bool is_dungeon(const point &p);
    void set_dungeon(const int x, const int y);
    void unset_dungeon(const int x, const int y);

    //
    // Used in lighting, so inlined
    //
    inline bool is_oob (const int x, const int y, const int z)
    {_
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT) ||
                (z < 0) || (z >= MAP_DEPTH));
    }

    inline bool is_oob (const int x, const int y)
    {_
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT));
    }

    inline bool is_oob (const fpoint p)
    {_
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    inline bool is_oob (const point p)
    {_
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    inline bool is_visited (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_visited, p.x, p.y));
    }

    inline bool is_visited (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_visited, x, y));
    }

    inline void set_visited (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_visited, x, y, true);
    }

    inline void unset_visited (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_visited, x, y, false);
    }

    //
    // Used in lighting, so inlined
    //
    inline bool is_gfx_large_shadow (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_gfx_large_shadow, p.x, p.y));
    }

    inline bool is_gfx_large_shadow (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_gfx_large_shadow, x, y));
    }

    inline void set_gfx_large_shadow (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_gfx_large_shadow, x, y, true);
    }

    inline void unset_gfx_large_shadow (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_gfx_large_shadow, x, y, false);
    }

    void init(point3d at, int seed);
    const char *to_cstring(void);
    std::string to_string(void);
    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void log_(const char *fmt, va_list args); // compile error without
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg_(const char *fmt, va_list args); // compile error without
    friend std::ostream& operator<<(std::ostream &out, Bits<const Level & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<Level &> my);
};

class World {
public:
    std::array<
      std::array<
        std::array<Levelp, LEVELS_DEEP>,
                           LEVELS_DOWN>,
                           LEVELS_ACROSS>
          levels {};
    //
    // Which level in the world
    //
    point3d at;

    void clear(void);
    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
    void new_level_at(point3d at, int seed);
    friend std::ostream& operator<<(std::ostream &out, Bits<const World & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<World &> my);
};

typedef class Config_ {
public:
    bool               fps_counter                  = true;
#ifdef ENABLE_INVERTED_GFX
    bool               gfx_inverted                 = true;
#else
    bool               gfx_inverted                 = false;
#endif
    bool               gfx_minimap                  = true;
    bool               gfx_show_hidden              = false;
    bool               gfx_lights                   = true;
    uint32_t           gfx_zoom                     = 4;
    bool               gfx_vsync_enable             = true;
    bool               debug_mode                   = false;
    uint32_t           sound_volume                 = {MIX_MAX_VOLUME / 2};
    uint32_t           music_volume                 = {MIX_MAX_VOLUME / 2};
    bool               fullscreen                   = false;
    bool               allow_highdpi                = false;
    //
    // This is the window size.
    //
    int32_t            outer_pix_width              = {};
    int32_t            outer_pix_height             = {};
    //
    // This is the virtual size of the game within the above window.
    //
    int32_t            inner_pix_width              = {};
    int32_t            inner_pix_height             = {};
    //
    // The ratiou of outer to inner
    //
    int32_t            scale_pix_width              = {};
    int32_t            scale_pix_height             = {};
    double             video_w_h_ratio              = {};
    double             tile_pix_width               = {};
    double             tile_pix_height              = {};
    double             one_pixel_width              = {};
    double             one_pixel_height             = {};
    double             ascii_gl_width               = {};
    double             ascii_gl_height              = {};
    double             tile_pixel_width             = {};
    double             tile_pixel_height            = {};
    uint32_t           sdl_delay                    = 1;
    uint32_t           key_map_up                   = {SDL_SCANCODE_UP};
    uint32_t           key_map_down                 = {SDL_SCANCODE_DOWN};
    uint32_t           key_map_left                 = {SDL_SCANCODE_LEFT};
    uint32_t           key_map_right                = {SDL_SCANCODE_RIGHT};
    uint32_t           key_move_up                  = {SDL_SCANCODE_W};
    uint32_t           key_move_down                = {SDL_SCANCODE_S};
    uint32_t           key_move_left                = {SDL_SCANCODE_A};
    uint32_t           key_move_right               = {SDL_SCANCODE_D};
    uint32_t           key_attack                   = {SDL_SCANCODE_SPACE};
    uint32_t           key_wait                     = {SDL_SCANCODE_PERIOD};
    uint32_t           key_load                     = {SDL_SCANCODE_F11};
    uint32_t           key_save                     = {SDL_SCANCODE_F12};
    uint32_t           key_todo1                  = {SDL_SCANCODE_Z};
    uint32_t           key_todo2                 = {SDL_SCANCODE_X};
    uint32_t           key_pause                    = {SDL_SCANCODE_P};
    uint32_t           key_help                     = {SDL_SCANCODE_H};
    uint32_t           key_quit                     = {SDL_SCANCODE_Q};

    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
} Config;
std::ostream& operator<<(std::ostream &out, Bits<const Config & > const my);
std::istream& operator>>(std::istream &in, Bits<Config &> my);

class Game {
public:
    Game (void) {}
    Game (std::string appdata);
    bool load(std::string save_file, class Game &target);
    bool paused(void);
    bool save(std::string save_file);
    void config_gfx_select(void);
    void config_other_select(void);
    void config_sound_select(void);
    void config_keyboard_select(void);
    void config_top_select(void);
    void dead_select(const char *reason);
    void display(void);
    void fini(void);
    void hard_pause(void);
    void hard_unpause(void);
    void init(void);
    void load(int slot);
    void load(void);
    void load_config(void);
    void load_select(void);
    void main_menu_select(void);
    void new_game(void);
    void pause_select(void);
    void quit_select(void);
    void help_select(void);
    void save(int slot);
    void save(void);
    void save_config(void);
    void save_select(void);
    void soft_pause(void);
    void soft_unpause(void);

    //
    // Save file name, contains the date and other useful save slot info
    //
    std::string        version = "" VERSION "";
    int                save_slot {};
    std::string        save_meta;
    std::string        save_file;
    std::string        appdata;
    std::string        saved_dir;

    Config             config;
    World              world;

    //
    // Where we are in the world.
    //
    point3d            current_level;

    //
    // All randomness jumps off of this as the root
    //
    int                seed {};

    //
    // Mouse cursor
    //
    fpoint             mouse_over;

    //
    // Current framerate
    //
    uint32_t           fps_value = {};

    //
    // Soft pause is user initiated. Hard is when a menu is on screen.
    //
    bool               soft_paused = false;
    bool               hard_paused = false;
    timestamp_t        last_pause {};

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////

    //
    // Last cursor path shown.
    //
    std::vector<point> cursor_move_path;

    //
    // How to reach the player. Updated each move.
    //
    Dmap               *player_dmap {};

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    /////////////////////////////////////////////////////////////////////////

    //
    // Game is afoot
    //
    bool               started = false;

    friend std::ostream& operator<<(std::ostream &out,
                                    Bits<const class Game & > const my);
    friend std::istream& operator>>(std::istream &in,
                                    Bits<class Game &> my);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
};

extern class Game *game;
extern class World *world;
extern class Level *level;
extern struct Thing_ *player;
extern bool thing_map_black_and_white;

extern uint8_t game_mouse_down(int32_t x, int32_t y, uint32_t button);
extern uint8_t game_mouse_up(int32_t x, int32_t y, uint32_t button);
extern void game_main_menu_hide(void);
extern void player_tick(void);

//
// Find an existing thing.
//
static inline Thingp thing_find (const uint32_t id)
{_
    return (level->find_thing_ptr(id));
}

#endif
