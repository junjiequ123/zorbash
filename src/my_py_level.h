//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_PY_LEVEL_H_
#define _MY_PY_LEVEL_H_
#include <Python.h>

PyObject *level_get_all(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_flood_fill_get_all_things(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_add_(PyObject *obj, PyObject *args, PyObject *keywds);

PyObject *level_is_able_to_change_levels_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_fall_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_see_through_doors_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_walk_through_walls_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_acid_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_acid_lover_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_active_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_alive_monst_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_always_hit_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ascend_dungeon_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ascend_sewer_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_attackable_by_monst_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_attackable_by_player_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_auto_collect_item_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bag_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bleeder_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_blood_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_blood_splatter_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bloodied_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_brazier_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr99_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrier_of_treasure_class_a_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrier_of_treasure_class_b_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrier_of_treasure_class_c_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrying_item_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_carrying_treasure_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_chasm_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_collect_as_keys_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_collectable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_combustible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_corpse_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_corpse_on_death_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_corridor_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_critical_to_level_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_can_hover_over_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_can_hover_over_but_needs_double_click_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_cursor_path_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dead_on_shove_at(PyObject *obj, PyObject *args, PyObject *keywds);
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
PyObject *level_is_dir_tl_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_tr_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dir_up_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dirt_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_door_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_droppable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ethereal_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_explosion_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_extreme_hazard_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_fearless_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_fire_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_very_combustible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_floating_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_floor_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_floor_deco_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_food_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_food_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_water_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_gold_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_hazard_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_humanoid_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_hunger_insatiable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_intelligent_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_interesting_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_carrier_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_collected_as_gold_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_item_not_stackable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_baby_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_baby_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jelly_parent_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jumper_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jumper_chance_d1000_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jumper_distance_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_jumper_on_low_hp_chance_d1000_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_key_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_killed_on_hit_or_miss_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_killed_on_hitting_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_target_select_automatically_when_chosen_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_lava_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_light_blocker_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_living_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_loggable_for_important_stuff_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_loggable_for_unimportant_stuff_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_meat_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_meat_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_minion_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_minion_generator_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_monst_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_moveable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_movement_blocking_hard_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_movement_blocking_soft_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_msg_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_no_tile_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_on_firing_at_something(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_player_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_poison_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_loves_poison_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_potion_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_potion_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_projectile_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_removeable_if_out_of_slots_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_resurrectable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ripple_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rock_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr1_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr2_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr3_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr4_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr5_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr6_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr7_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr8_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr9_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr10_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr11_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr12_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr13_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr14_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr15_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr16_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr17_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr18_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr19_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr20_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr21_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr22_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr23_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr24_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr25_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr26_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr27_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr28_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr29_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr30_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr31_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr32_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr33_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr34_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr35_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr36_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr37_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr38_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr39_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr40_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr41_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr42_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr43_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr44_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr45_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr46_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr47_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr48_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr49_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr50_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr51_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr52_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr53_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr54_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr55_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr56_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr57_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr58_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr59_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr60_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr61_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr62_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr63_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr64_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr65_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr66_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr67_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr68_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr69_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr70_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr71_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr72_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr73_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr74_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr75_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr76_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr77_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_rrr78_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_skillstone_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_enchant_level_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_enchant_max_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_enchantstone_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_enchantable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_indestructible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bones_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_soft_body_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_foilage_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_very_small_shadow_caster_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_dry_fungus_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_bridge_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_barrel_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_burnable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wand_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_loves_fire_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_projectile_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_gfx_flickers_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_laser_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_able_to_fire_at_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_ethereal_minion_generator_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_secret_door_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_sewer_wall_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_shallow_water_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_water_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_shovable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_shown_on_leftbar_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_shown_uniquely_on_leftbar_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_skill_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_smoke_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_spawner_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_stamina_check_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_steal_item_chance_d1000_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_temporary_bag_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_throwable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_thrown_automatically_when_chosen_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_torch_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_class_a_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_class_b_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_class_c_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_treasure_eater_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_undead_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_usable_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_used_automatically_when_selected_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_used_when_thrown_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_visible_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wall_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wall_dungeon_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_wand_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_water_lover_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_weapon_at(PyObject *obj, PyObject *args, PyObject *keywds);
PyObject *level_is_weapon_wielder_at(PyObject *obj, PyObject *args, PyObject *keywds);
#endif
