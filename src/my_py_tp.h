/*
 * Copyright (C) 2018 goblinhack@gmail.com
 
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_PY_TP_H_
#define _MY_PY_TP_H_
#include <Python.h>

PyObject *tp_load_(PyObject *obj, PyObject *args, PyObject *keywds);

#define TP_SET_PROTO(__field__)                                                     \
PyObject *tp_set_ ## __field__ (PyObject *obj, PyObject *args, PyObject *keywds);

#define TP_SET_DECL(__field__)                                                      \
    {"tp_set_" #__field__,                                                      \
        (PyCFunction)tp_set_ ## __field__,                                      \
        METH_VARARGS | METH_KEYWORDS,                                           \
        "set a " #__field__ " in a thing template"},                            \

PyObject *tp_update_(PyObject *obj, PyObject *args, PyObject *keywds);

TP_SET_PROTO(tile)
TP_SET_PROTO(left_tile)
TP_SET_PROTO(right_tile)
TP_SET_PROTO(top_tile)
TP_SET_PROTO(bot_tile)
TP_SET_PROTO(bl_tile)
TP_SET_PROTO(br_tile)
TP_SET_PROTO(tl_tile)
TP_SET_PROTO(tr_tile)
TP_SET_PROTO(blit_top_off)
TP_SET_PROTO(blit_bot_off)
TP_SET_PROTO(blit_left_off)
TP_SET_PROTO(blit_right_off)
TP_SET_PROTO(short_name)
TP_SET_PROTO(raw_name)
TP_SET_PROTO(weapon_use_anim)
TP_SET_PROTO(str_zzz1)
TP_SET_PROTO(str_zzz2)
TP_SET_PROTO(str_zzz3)
TP_SET_PROTO(str_zzz4)
TP_SET_PROTO(str_zzz5)
TP_SET_PROTO(str_zzz6)
TP_SET_PROTO(str_zzz7)
TP_SET_PROTO(str_zzz8)
TP_SET_PROTO(str_zzz9)
TP_SET_PROTO(str_zzz10)
TP_SET_PROTO(str_zzz11)
TP_SET_PROTO(str_zzz12)
TP_SET_PROTO(str_zzz13)
TP_SET_PROTO(str_zzz14)
TP_SET_PROTO(str_zzz15)
TP_SET_PROTO(str_zzz16)
TP_SET_PROTO(str_zzz17)
TP_SET_PROTO(str_zzz18)
TP_SET_PROTO(weapon_carry_anim)
TP_SET_PROTO(weapon_use_anim)
TP_SET_PROTO(is_animated)
TP_SET_PROTO(is_animated_no_dir)
TP_SET_PROTO(is_animation)
TP_SET_PROTO(is_door)
TP_SET_PROTO(is_water)
TP_SET_PROTO(is_lava)
TP_SET_PROTO(is_monst)
TP_SET_PROTO(is_player)
TP_SET_PROTO(is_rrr1)
TP_SET_PROTO(is_rrr2)
TP_SET_PROTO(is_rrr3)
TP_SET_PROTO(is_rrr4)
TP_SET_PROTO(is_rrr5)
TP_SET_PROTO(is_rrr6)
TP_SET_PROTO(is_rrr7)
TP_SET_PROTO(is_rrr8)
TP_SET_PROTO(is_rrr9)
TP_SET_PROTO(is_rrr10)
TP_SET_PROTO(is_rrr11)
TP_SET_PROTO(is_rrr12)
TP_SET_PROTO(is_rrr13)
TP_SET_PROTO(is_rrr14)
TP_SET_PROTO(is_rrr15)
TP_SET_PROTO(is_rrr16)
TP_SET_PROTO(is_rrr17)
TP_SET_PROTO(is_rrr18)
TP_SET_PROTO(is_blit_off_center)
TP_SET_PROTO(is_boring)
TP_SET_PROTO(is_exit)
TP_SET_PROTO(is_entrance)
TP_SET_PROTO(move_delay_hundredths)
TP_SET_PROTO(weapon_use_delay_hundredths)
TP_SET_PROTO(for_collision_use_box)
TP_SET_PROTO(for_collision_use_circle)
TP_SET_PROTO(weapon_damage)
TP_SET_PROTO(is_projectile)
TP_SET_PROTO(is_explosion)
TP_SET_PROTO(is_combustable)
TP_SET_PROTO(is_spikes)
TP_SET_PROTO(collision_priority)
TP_SET_PROTO(weapon_use_distance)
TP_SET_PROTO(is_weapon_carry_anim)
TP_SET_PROTO(is_weapon_use_effect)
TP_SET_PROTO(is_weapon)
TP_SET_PROTO(is_outlined)
TP_SET_PROTO(is_shadow_caster)
TP_SET_PROTO(is_animated_walk_flip)
TP_SET_PROTO(z_depth)
TP_SET_PROTO(is_movable)
TP_SET_PROTO(is_hidden)
TP_SET_PROTO(is_dirt)
TP_SET_PROTO(is_sand)
TP_SET_PROTO(is_plant)
TP_SET_PROTO(is_tree)
TP_SET_PROTO(is_bridge)
TP_SET_PROTO(is_movement_blocking)
TP_SET_PROTO(is_entrance)
TP_SET_PROTO(is_exit)
TP_SET_PROTO(is_chasm_smoke)
TP_SET_PROTO(is_key)
TP_SET_PROTO(is_dusty)
TP_SET_PROTO(is_corridor)
TP_SET_PROTO(is_healing)
TP_SET_PROTO(is_armor)
TP_SET_PROTO(is_magical)
TP_SET_PROTO(is_shadow_caster)
TP_SET_PROTO(is_sleeping)
TP_SET_PROTO(is_wall)
TP_SET_PROTO(is_door)
TP_SET_PROTO(is_water)
TP_SET_PROTO(is_lava)
TP_SET_PROTO(is_floor)
#endif
