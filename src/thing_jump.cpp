//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

bool Thing::try_to_jump (point to)
{
    //
    // No rapid boinging
    //
    if (is_jumping) {
        return false;
    }

    auto x = to.x;
    auto y = to.y;

    if (is_player()) {
        log("try jump to %d,%d", x, y);
    }

    if (level->is_oob(x, y)) {_
        log("no, oob");
        if (is_player()) {
            MINICON("You can't jump into the void");
        }
        return false;
    }

    //
    // Block jumping over doors
    //
    if (!level->is_lit(x, y) && !level->is_visited(x, y)) {_
        log("no, is not lit or visited");
        if (is_player()) {
            MINICON("You can't jump into the unknown");
        }
        return false;
    }

    bool check_dest = true;

    if (is_player()) {
        check_dest = false;
    }

    auto fto = make_fpoint(to);

    //
    // Add some random delta for fun and some for diagonals
    //
    auto how_far_i_can_jump = (float) is_jumper_distance() +
        0.5 + (random_range(0, 100) / 100.0);

    if (distance(mid_at, fto) > how_far_i_can_jump) {
        auto u = (fto - mid_at);
        u.unit();
        u *= is_jumper_distance();
        fto = mid_at + u;
        to = make_point(fto);
        x = to.x;
        y = to.y;
        //
        // Not sure I want to. This allows for more fun.
        //
        // check_dest = true;
    }

    if (is_monst()) {
        if (distance(mid_at, fpoint(x, y)) < 2) {_
            log("no, too far");
            if (is_player()) {
                MINICON("You can't jump quite that far");
            }
            return false;
        }
    }

    //
    // No sneaky jumping onto doors to get passed them
    //
    if (level->is_movement_blocking_hard(x, y) ||
        level->is_movement_blocking_soft(x, y)) {_
        log("no, jump failed, into obstacle");
        if (is_player()) {
            MINICON("You can't jump quite into solid objects");
        }
        return false;
    }

    if (check_dest) {
        if (!level->is_dungeon(x, y)) {_
            log("no, jump failed, not dungeon");
            if (is_player()) {
                MINICON("You can't jump outside the dungeon");
            }
            return false;
        }

        if (level->is_entrance(x, y) ||
            level->is_monst(x, y)    ||
            level->is_exit(x, y)) {_
            log("no, jump failed, onto monst");
            if (is_player()) {
                MINICON("You can't quite into that");
            }
            return false;
        }

        if (will_avoid(point(x, y))) {_
            log("no, jump failed, avoid destination");
            if (is_player()) {
                MINICON("You can't quite onto that");
            }
            return false;
        }
    }

    auto src = (last_blit_tl + last_blit_br) / 2;
    auto dx = x - mid_at.x;
    auto dy = y - mid_at.y;
    auto tw = TILE_WIDTH;
    auto th = TILE_HEIGHT;
    auto sz = size(last_blit_br.x - last_blit_tl.x,
                   last_blit_br.y - last_blit_tl.y);
    point dst(src.x + dx * tw , src.y + dy * th );
    if (is_player()) {
        //
        // So the player is visible above light
        //
        level->new_external_particle(id, src, dst, sz, 500,
                                     tile_index_to_tile(tile_curr),
                                     false);
    } else {
        level->new_internal_particle(id, src, dst, sz, 500,
                                     tile_index_to_tile(tile_curr),
                                     false);
    }

    is_jumping = true;
    move_to_immediately(fpoint(x, y));

    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_carry_anim());
        if (w) {
            w->move_to_immediately(mid_at);
            w->is_jumping = true;
            level->new_external_particle(id, src, dst, sz, 500,
                                        tile_index_to_tile(w->tile_curr),
                                        (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()));
        }
    }

    if (get_weapon_id_use_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_use_anim());
        if (w) {
            w->move_to_immediately(mid_at);
            w->is_jumping = true;
            //
            // No, the weapon is shown as carry anim
            //
            level->new_external_particle(id, src, dst, sz, 500,
                                        tile_index_to_tile(w->tile_curr),
                                        (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()));
        }
    }

    //
    // Move carried items too as when we attack, we will use say the
    // carried sword and so it had better be in the same location.
    //
    for (auto oid : monstp->carrying) {
        auto w = level->thing_find(oid);
        if (w) {
            w->move_to_immediately(mid_at);
            w->is_jumping = true;
        }
    }

    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id.ok()) {_
        auto w = level->thing_find(on_fire_anim_id);
        if (w) {
            w->move_to_immediately(mid_at);
            w->is_jumping = true;
            level->new_external_particle(id, src, dst, sz, 500,
                                        tile_index_to_tile(w->tile_curr),
                                        (w->is_dir_br() || w->is_dir_right() || w->is_dir_tr()));
        }
    }

    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {
        if (!is_floating()) {
            if (level->is_water((int)mid_at.x, (int)mid_at.y)) {
                fpoint at(mid_at.x, mid_at.y);
                log("causes ripples");
                if (random_range(0, 1000) > 500) {
                    level->thing_new(tp_random_ripple()->name(), at);
                }
            }
        }
    }

    wobble(25);

    return (true);
}

bool Thing::try_to_jump (void)
{
    //
    // No rapid boinging
    //
    if (is_jumping) {
        return false;
    }

    int d = is_jumper_distance() / 2;
    int tries = d * d;

    while (tries-- > 0) {
        int x = random_range(mid_at.x - d, mid_at.x + d);
        int y = random_range(mid_at.y - d, mid_at.y + d);
        if (try_to_jump(point(x, y))) {
            return true;
        }
    }

    return (false);
}

void Thing::jump_end (void)
{
    if (!is_jumping) {
        return;
    }

    log("end of jump");
    is_jumping = false;

    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_carry_anim());
        if (w) {
            w->is_jumping = false;
        }
    }

    if (get_weapon_id_use_anim().ok()) {
        auto w = level->thing_find(get_weapon_id_use_anim());
        if (w) {
            w->is_jumping = false;
        }
    }

    //
    // Move carried items too as when we attack, we will use say the
    // carried sword and so it had better be in the same location.
    //
    for (auto oid : monstp->carrying) {
        auto o = level->thing_find(oid);
        if (o) {
            o->is_jumping = false;
        }
    }

    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id.ok()) {_
        auto w = level->thing_find(on_fire_anim_id);
        if (w) {
            w->is_jumping = false;
        }
    }

    collision_check_only(mid_at);
    location_check();

    //
    // Attack of opportunity
    //
    if (is_player()) {
        auto t = nearby_most_dangerous_thing_get();
        if (t) {
            std::string s = t->text_The() + " attacks as you land";
            MINICON("%s", s.c_str());
            game->tick_begin("monst attack as player landed");
        }
    }
    wobble(25);
}
