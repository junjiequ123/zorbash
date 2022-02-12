import my
import tp


def on_you_natural_attack(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_miss_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 75)
    my.tp_set_ai_detect_secret_doors(self, True)
    my.tp_set_ai_resent_count(self, 20)
    my.tp_set_ai_shove_chance_d1000(self, 500)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_eater(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_attack_meat(self, True)
    my.tp_set_attack_undead(self, True)
    my.tp_set_capacity_height(self, 10)
    my.tp_set_capacity_width(self, 10)
    my.tp_set_collateral_damage_pct(self, 50)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_damage_natural_attack_type(self, "claw")
    my.tp_set_damage_natural_dice(self, "1d4+2")
    my.tp_set_distance_avoid(self, 5)
    my.tp_set_distance_jump(self, 3)
    my.tp_set_distance_leader_max(self, 5)
    my.tp_set_distance_recruitment_max(self, 7)
    my.tp_set_distance_vision(self, 7)
    my.tp_set_environ_avoids_acid(self, 100)
    my.tp_set_environ_avoids_fire(self, 10)
    my.tp_set_environ_avoids_poison(self, 100)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_asleep(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "2d6")
    my.tp_set_hunger_clock_tick_frequency(self, 50)
    my.tp_set_hunger_health_pct(self, 95)
    my.tp_set_is_able_to_attack_mobs(self, True)
    my.tp_set_is_able_to_break_down_doors(self, True)
    my.tp_set_is_able_to_break_out_of_webs(self, True)
    my.tp_set_is_able_to_change_levels(self, True)
    my.tp_set_is_able_to_collect_keys(self, True)
    my.tp_set_is_able_to_enchant_items(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_follow(self, True)
    my.tp_set_is_able_to_jump(self, True)
    my.tp_set_is_able_to_learn_skills(self, True)
    my.tp_set_is_able_to_move_diagonally(self, True)
    my.tp_set_is_able_to_open_doors(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_able_to_shove(self, True)
    my.tp_set_is_able_to_sleep(self, True)
    my.tp_set_is_able_to_tire(self, True)
    my.tp_set_is_able_to_use_amulet(self, True)
    my.tp_set_is_able_to_use_boots(self, True)
    my.tp_set_is_able_to_use_cloak(self, True)
    my.tp_set_is_able_to_use_gauntlet(self, True)
    my.tp_set_is_able_to_use_rings(self, True)
    my.tp_set_is_able_to_use_wands(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_bleeder(self, True)
    my.tp_set_is_bony(self, True)
    my.tp_set_is_breather(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_explorer(self, True)
    my.tp_set_is_green_blooded(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_humanoid(self, True)
    my.tp_set_is_item_carrier(self, True)
    my.tp_set_is_item_collector(self, True)
    my.tp_set_is_living(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meat(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_move_speed(self, 100)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_steal_item_chance_d1000(self, 50)
    my.tp_set_is_tickable(self, True)
    my.tp_set_long_text_description(self, "A very lesser minion of Zorbash, Zorblins are small, green skinned beings that lair in caves, abandoned mines, despoiled dungeons and other dismal settings, otherwise known as their homes. They spend their time defending their natural habitat from invading marauders like you. However, they usually carry some meagre amounts of gold, dug out from the depths with their bare, shaking hands. Best to find out...")
    my.tp_set_monst_size(self, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(self, 10)
    my.tp_set_noise_on_moving_or_being_carried(self, 5)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "zorb_all.on_death()")
    my.tp_set_on_death_drop_all_items(self, True)
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "zorb_all.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(self, "zorb_all.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(self, "zorb_all.on_you_natural_attack()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stamina(self, 100)
    my.tp_set_stat_att_penalty_when_idle(self, 0)
    my.tp_set_stat_att_penalty_when_idle_max(self, 0)
    my.tp_set_stat_att_penalty_when_in_deep_water(self, 5)
    my.tp_set_stat_att_penalty_when_in_shallow_water(self, 2)
    my.tp_set_stat_att_penalty_when_stuck(self, 5)
    my.tp_set_stat_att_penalty_when_stuck_max(self, 5)
    my.tp_set_stat_con(self, 10)
    my.tp_set_stat_def(self, 10)
    my.tp_set_stat_def_penalty_when_idle(self, 5)
    my.tp_set_stat_def_penalty_when_idle_max(self, 5)
    my.tp_set_stat_def_penalty_when_in_deep_water(self, 5)
    my.tp_set_stat_def_penalty_when_in_shallow_water(self, 2)
    my.tp_set_stat_def_penalty_when_stuck(self, 10)
    my.tp_set_stat_def_penalty_when_stuck_max(self, 15)
    my.tp_set_stat_dex(self, 12)
    my.tp_set_stat_luck(self, 8)
    my.tp_set_stat_str(self, 8)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_hits(self, "claws")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)
    return self
