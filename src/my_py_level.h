//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PY_LEVEL_H_
#define _MY_PY_LEVEL_H_
#include <Python.h>

PyObject *level_add_(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_remember_enemies_for_n_ticks_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_enchant_level_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_enchant_max_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_flood_fill_get_all_things(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_get_all(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_flickers_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_long_shadow_caster_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_solid_shadow_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_very_short_shadow_caster_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_water_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_change_levels_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_fall_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_fire_at_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_see_through_doors_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_walk_through_walls_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_acid_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_acid_lover_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_alive_monst_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_alive_on_end_of_anim_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_always_hit_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ascend_dungeon_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ascend_sewer_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_attackable_by_monst_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_attackable_by_player_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_auto_collect_item_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bag_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bag_item_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bag_item_container_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bag_item_not_stackable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_barrel_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bleeder_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_blood_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bloodied_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_blood_splatter_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bones_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_brazier_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bridge_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_burnable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrier_of_treasure_class_a_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrier_of_treasure_class_b_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrier_of_treasure_class_c_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrying_item_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrying_treasure_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_chasm_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_collectable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_collect_as_keys_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_collected_as_gold_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_combustible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_corpse_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_corpse_on_death_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_corridor_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_critical_to_level_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_can_hover_over_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_can_hover_over_x2_click_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_path_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dead_on_end_of_anim_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dead_on_shove_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_debug_path_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_debug_type_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_deep_water_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_descend_dungeon_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_descend_sewer_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_described_when_hovering_over_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_bl_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_br_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_down_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_left_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_none_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_right_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dirt_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_tl_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_tr_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_up_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_door_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_droppable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dry_grass_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_enchantable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_enchantstone_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ethereal_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ethereal_minion_generator_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_explosion_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_extreme_hazard_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_fearless_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_fire_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_floating_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_floor_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_floor_deco_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_foilage_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_food_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_food_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_gold_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_hazard_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_hittable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_humanoid_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_hunger_insatiable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_indestructible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_intelligent_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_interesting_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_carrier_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_baby_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_baby_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_parent_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_jump_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_random_jump_chance_d1000_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_jump_distance_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_jump_on_low_hp_chance_d1000_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_key_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_collect_keys_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_killed_on_hit_or_miss_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_killed_on_hitting_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_laser_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_lava_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_light_blocker_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_living_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_loggable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_loggable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_meat_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_meat_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_minion_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_minion_generator_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_monst_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_moveable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_obs_wall_or_door_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_obs_destructable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_msg_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_no_tile_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_on_firing_at_something(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_openable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_player_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_poison_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_potion_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_potion_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_projectile_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_removeable_if_out_of_slots_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_resurrectable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ripple_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rock_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag10_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag11_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag12_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag13_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag14_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag15_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag16_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag17_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag18_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag19_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag1_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag20_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag21_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag22_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag23_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag24_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag25_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag26_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag27_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag28_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag29_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag2_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag30_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag31_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag32_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag33_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag34_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag35_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag36_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag37_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag38_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag39_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag3_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag40_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag41_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_detect_secret_doors_when_close_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_break_down_doors_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_break_out_of_webs_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_break_out_of_webs_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_open_doors_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_exit_finder_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_level_explorer_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rusty_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag4_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_learn_skills_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_enchant_weapons_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_able_to_attack_generators_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_wanderer_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_organic_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_glass_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_stone_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_organic_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_metal_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wooden_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag5_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_engulfer_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_health_booster_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag6_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag7_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag8_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_unused_flag9_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_secret_door_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_sewer_wall_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_shallow_water_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_shovable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_skill_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_skillstone_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_smoke_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_soft_body_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_spawner_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_spiderweb_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_tire_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_steal_item_chance_d1000_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_engulf_chance_d1000_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_sticky_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_shovable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_sword_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_target_auto_select_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_throwable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_auto_throw_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_tickable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_tmp_thing_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_torch_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_class_a_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_class_b_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_class_c_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_type_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_type_chest_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_ai_is_item_collector_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_type_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_undead_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_usable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_auto_use_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_used_when_thrown_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_very_combustible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_visible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wall_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wall_dungeon_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wand_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wand_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_water_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_water_lover_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_weapon_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_weapon_wielder_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_loves_fire_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_loves_poison_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_loves_spiderwebs_at(PyObject *obj, PyObject *args, PyObject *keywds);
#endif
