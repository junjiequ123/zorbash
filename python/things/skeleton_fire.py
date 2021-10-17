import zx
import tp

def on_you_bite_attack(me, x, y):
    sound = "growl{}".format(zx.non_pcg_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_you_are_hit(me, hitter, real_hitter, x, y, crit, bite, poison, damage):
    sound = "hiss{}".format(zx.non_pcg_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_you_miss_do(me, hitter, x, y):
    sound = "hiss{}".format(zx.non_pcg_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_death(me, x, y):
    if zx.non_pcg_randint(1, 2) == 1:
        if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, "bones1"):
            zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, "bones1")
    else:
        if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, "bones2"):
            zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, "bones2")

def on_firing_at_something(me, target, x, y): # Return True on doing an action
    if zx.pcg_randint(1, 100) < 10:
        zx.thing_fire_at(me, "projectile_fire", target)
        zx.thing_sound_play_channel(me, zx.CHANNEL_EXPLOSION, "explosion_b")
        return True
    return False

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_avoid_distance(4)
    mytp.set_ai_is_able_to_attack_generators(False)
    mytp.set_ai_is_able_to_break_down_doors(False)
    mytp.set_ai_is_able_to_break_out_of_webs(False)
    mytp.set_ai_is_able_to_collect_keys(False)
    mytp.set_ai_is_able_to_detect_secret_doors_when_close(False)
    mytp.set_ai_is_able_to_enchant_weapons(False)
    mytp.set_ai_is_able_to_jump(False)
    mytp.set_ai_is_able_to_learn_skills(False)
    mytp.set_ai_is_able_to_open_doors(False)
    mytp.set_ai_is_able_to_see_through_doors(False)
    mytp.set_ai_is_able_to_shove(True)
    mytp.set_ai_is_able_to_walk_through_walls(False)
    mytp.set_ai_is_exit_finder(False)
    mytp.set_ai_is_item_collector(False)
    mytp.set_ai_is_level_explorer(False)
    mytp.set_ai_obstacle(False)
    mytp.set_ai_resent_count(10)
    mytp.set_ai_scent_distance(10)
    mytp.set_ai_shove_chance_d1000(200)
    mytp.set_ai_unprovoked_attack_chance_d1000(1000)
    mytp.set_ai_vision_distance(7)
    mytp.set_ai_vision_distance(8)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_blood(False)
    mytp.set_attack_eater(False)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_living(False)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_attack_undead(False)
    mytp.set_collision_attack(True)
    mytp.set_collision_box(False)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(False)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_bite_dice("1d3")
    mytp.set_damage_melee_dice("1d2")
    mytp.set_enchant_level(False)
    mytp.set_enchant_max(False)
    mytp.set_environ_damage_doubled_from_acid(False)
    mytp.set_environ_damage_doubled_from_fire(False)
    mytp.set_environ_damage_doubled_from_poison(False)
    mytp.set_environ_damage_doubled_from_water(True)
    mytp.set_environ_dislikes_acid(False)
    mytp.set_environ_dislikes_fire(False)
    mytp.set_environ_dislikes_poison(False)
    mytp.set_environ_dislikes_water(100)
    mytp.set_environ_hates_acid(False)
    mytp.set_environ_hates_fire(False)
    mytp.set_environ_hates_poison(False)
    mytp.set_environ_hates_water(True)
    mytp.set_environ_loves_acid(False)
    mytp.set_environ_loves_fire(True)
    mytp.set_environ_loves_poison(True)
    mytp.set_environ_loves_spiderwebs(False)
    mytp.set_environ_loves_water(False)
    mytp.set_gfx_an_animation_only(False)
    mytp.set_gfx_anim_attack("attack_claws")
    mytp.set_gfx_animated(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated_can_vflip(False)
    mytp.set_gfx_animated_no_dir(False)
    mytp.set_gfx_attack_anim(False)
    mytp.set_gfx_bounce_always(False)
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_dead_anim(False)
    mytp.set_gfx_flickers(False)
    mytp.set_gfx_glows(True)
    mytp.set_gfx_health_bar_autohide(False)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_long_shadow_caster(False)
    mytp.set_gfx_on_fire_anim(False)
    mytp.set_gfx_oversized_and_on_floor(False)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_shown_in_bg(False)
    mytp.set_gfx_solid_shadow(False)
    mytp.set_gfx_very_short_shadow_caster(False)
    mytp.set_gfx_water(False)
    mytp.set_gfx_weapon_carry_anim(False)
    mytp.set_health_hunger_pct(95)
    mytp.set_health_initial_dice("2")
    mytp.set_is_able_to_change_levels(False)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_fire_at(True)
    mytp.set_is_able_to_tire(False)
    mytp.set_is_acid(False)
    mytp.set_is_alive_on_end_of_anim(False)
    mytp.set_is_always_hit(False)
    mytp.set_is_ascend_dungeon(False)
    mytp.set_is_ascend_sewer(False)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_auto_collect_item(False)
    mytp.set_is_auto_throw(False)
    mytp.set_is_auto_use(False)
    mytp.set_is_bag(False)
    mytp.set_is_bag_item(False)
    mytp.set_is_bag_item_container(False)
    mytp.set_is_bag_item_not_stackable(False)
    mytp.set_is_barrel(False)
    mytp.set_is_bleeder(False)
    mytp.set_is_blood(False)
    mytp.set_is_blood_eater(False)
    mytp.set_is_blood_splatter(False)
    mytp.set_is_bones(False)
    mytp.set_is_brazier(False)
    mytp.set_is_bridge(False)
    mytp.set_is_buff(False)
    mytp.set_is_burnable(False)
    mytp.set_is_carrier_of_treasure_class_a(True)
    mytp.set_is_carrier_of_treasure_class_b(False)
    mytp.set_is_carrier_of_treasure_class_c(False)
    mytp.set_is_chasm(False)
    mytp.set_is_collect_as_keys(False)
    mytp.set_is_collectable(False)
    mytp.set_is_collected_as_gold(False)
    mytp.set_is_combustible(False)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_corridor(False)
    mytp.set_is_critical_to_level(False)
    mytp.set_is_cursor(False)
    mytp.set_is_cursor_can_hover_over(False)
    mytp.set_is_cursor_can_hover_over_x2_click(False)
    mytp.set_is_cursor_path(False)
    mytp.set_is_cursor_path_hazard_for_player(False)
    mytp.set_is_dead_on_end_of_anim(False)
    mytp.set_is_dead_on_shove(False)
    mytp.set_is_debuff(False)
    mytp.set_is_debug_path(False)
    mytp.set_is_debug_type(False)
    mytp.set_is_deep_water(False)
    mytp.set_is_descend_dungeon(False)
    mytp.set_is_descend_sewer(False)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_destroyed_on_hit_or_miss(False)
    mytp.set_is_destroyed_on_hitting(False)
    mytp.set_is_dirt(False)
    mytp.set_is_door(False)
    mytp.set_is_droppable(False)
    mytp.set_is_dry_grass(False)
    mytp.set_is_enchantable(False)
    mytp.set_is_enchantstone(False)
    mytp.set_is_engulfer(False)
    mytp.set_is_ethereal(False)
    mytp.set_is_ethereal_minion_generator(False)
    mytp.set_is_explosion(False)
    mytp.set_is_fearless(False) # cannot enable as negates avoid_distance
    mytp.set_is_fire(False)
    mytp.set_is_floating(False)
    mytp.set_is_floor(False)
    mytp.set_is_floor_deco(False)
    mytp.set_is_foilage(False)
    mytp.set_is_food(False)
    mytp.set_is_food_eater(False)
    mytp.set_is_glass(False)
    mytp.set_is_gold(False)
    mytp.set_is_hazard(False)
    mytp.set_is_health_booster(False)
    mytp.set_is_hittable(True)
    mytp.set_is_humanoid(False)
    mytp.set_is_hunger_insatiable(True)
    mytp.set_is_indestructible(False)
    mytp.set_is_intelligent(True)
    mytp.set_is_interesting(False)
    mytp.set_is_item(False)
    mytp.set_is_item_carrier(False)
    mytp.set_is_item_eater(False)
    mytp.set_is_item_organic(False)
    mytp.set_is_jelly(False)
    mytp.set_is_jelly_baby(False)
    mytp.set_is_jelly_baby_eater(False)
    mytp.set_is_jelly_eater(False)
    mytp.set_is_jelly_parent(False)
    mytp.set_is_key(False)
    mytp.set_is_laser(False)
    mytp.set_is_lava(False)
    mytp.set_is_light_blocker(False)
    mytp.set_is_living(False)
    mytp.set_is_loggable(True)
    mytp.set_is_meat(False)
    mytp.set_is_meat_eater(False)
    mytp.set_is_metal(False)
    mytp.set_is_minion(True)
    mytp.set_is_minion_generator(False)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_msg(False)
    mytp.set_is_no_tile(False)
    mytp.set_is_obs_destructable(False)
    mytp.set_is_obs_wall_or_door(False)
    mytp.set_is_openable(False)
    mytp.set_is_organic(False)
    mytp.set_is_player(False)
    mytp.set_is_poison(False)
    mytp.set_is_potion(False)
    mytp.set_is_potion_eater(False)
    mytp.set_is_projectile(False)
    mytp.set_is_removeable_if_out_of_slots(False)
    mytp.set_is_resurrectable(True)
    mytp.set_is_ripple(False)
    mytp.set_is_rock(False)
    mytp.set_is_rusty(False)
    mytp.set_is_secret_door(False)
    mytp.set_is_sewer_wall(False)
    mytp.set_is_shallow_water(False)
    mytp.set_is_shovable(True)
    mytp.set_is_skill(False)
    mytp.set_is_skillstone(False)
    mytp.set_is_smoke(False)
    mytp.set_is_soft_body(False)
    mytp.set_is_spawner(False)
    mytp.set_is_spiderweb(False)
    mytp.set_is_sticky(False)
    mytp.set_is_stone(False)
    mytp.set_is_sword(False)
    mytp.set_is_target_auto_select(False)
    mytp.set_is_the_grid(False)
    mytp.set_is_throwable(False)
    mytp.set_is_tickable(True)
    mytp.set_is_tmp_thing(False)
    mytp.set_is_torch(False)
    mytp.set_is_treasure_class_a(False)
    mytp.set_is_treasure_class_b(False)
    mytp.set_is_treasure_class_c(False)
    mytp.set_is_treasure_type(False)
    mytp.set_is_treasure_type_chest(False)
    mytp.set_is_treasure_type_eater(False)
    mytp.set_is_undead(True)
    mytp.set_is_usable(False)
    mytp.set_is_used_when_thrown(False)
    mytp.set_is_very_combustible(False)
    mytp.set_is_wall(False)
    mytp.set_is_wall_dungeon(False)
    mytp.set_is_wand(False)
    mytp.set_is_wand_eater(False)
    mytp.set_is_weapon_wielder(True)
    mytp.set_is_wooden(False)
    mytp.set_light_color("yellow")
    mytp.set_light_strength(2)
    mytp.set_long_text_description("A collection of tortured burning bones, driven to wander the dungeon forever. Or at least until you release them. Such creatures abhor the cleansing powers of water.")
    mytp.set_minion_leash_distance(6)
    mytp.set_monst_size(zx.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_you_bite_attack_do("skeleton_fire.on_you_bite_attack()")
    mytp.set_on_death_do("skeleton_fire.on_death()")
    mytp.set_on_death_drop_all_items(False)
    mytp.set_on_death_is_open(False)
    mytp.set_on_firing_at_something_do("skeleton_fire.on_firing_at_something()")
    mytp.set_on_you_are_hit_do("skeleton_fire.on_you_are_hit()")
    mytp.set_on_you_miss_do_do("skeleton_fire.on_you_miss_do()")
    mytp.set_rarity(zx.RARITY_COMMON)
    mytp.set_resurrect_dice("1d20+30")
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(9)
    mytp.set_stat_defence(9)
    mytp.set_stat_strength(9)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("The burning bones of one surprised to be moving again and literally on fire.")
    mytp.set_text_hits("claws")
    mytp.set_unused_flag1(False)
    mytp.set_unused_flag10(False)
    mytp.set_unused_flag11(False)
    mytp.set_unused_flag12(False)
    mytp.set_unused_flag13(False)
    mytp.set_unused_flag14(False)
    mytp.set_unused_flag15(False)
    mytp.set_unused_flag16(False)
    mytp.set_unused_flag17(False)
    mytp.set_unused_flag18(False)
    mytp.set_unused_flag19(False)
    mytp.set_unused_flag2(False)
    mytp.set_unused_flag20(False)
    mytp.set_unused_flag21(False)
    mytp.set_unused_flag22(False)
    mytp.set_unused_flag23(False)
    mytp.set_unused_flag24(False)
    mytp.set_unused_flag25(False)
    mytp.set_unused_flag26(False)
    mytp.set_unused_flag27(False)
    mytp.set_unused_flag28(False)
    mytp.set_unused_flag29(False)
    mytp.set_unused_flag3(False)
    mytp.set_unused_flag30(False)
    mytp.set_unused_flag31(False)
    mytp.set_unused_flag32(False)
    mytp.set_unused_flag4(False)
    mytp.set_unused_flag5(False)
    mytp.set_unused_flag6(False)
    mytp.set_unused_flag7(False)
    mytp.set_unused_flag8(False)
    mytp.set_unused_flag9(False)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile("skeleton_fire.1", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_left=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_up=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_down=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_right=True, is_moving=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_left=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_left=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_left=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_left=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_up=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_up=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_up=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_up=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_down=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_down=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_down=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_down=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_right=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_right=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_right=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_right=True, delay_ms=delay)

    mytp.set_tile("skeleton_fire.1", is_dir_none=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2", is_dir_none=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3", is_dir_none=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4", is_dir_none=True, delay_ms=delay)

    delay = 20
    mytp.set_tile("skeleton_fire.1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.4.dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    mytp.set_tile("skeleton_fire.4.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.3.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.2.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile("skeleton_fire.1.dead", is_resurrecting=True, is_end_of_anim=True, is_alive_on_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="skeleton_fire", text_name="burning skeleton")

init()
