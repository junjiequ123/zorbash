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
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")


def on_born(me, x, y):
    it = my.level_spawn_at_thing(me, "spiderweb")
    if it != 0:
        my.thing_set_mob(me, it)


def on_firing_at_something(me, target, x, y):  # Return True on doing an action
    if my.pcg_randint(1, 100) < 10:
        my.thing_fire_at(me, "projectile_web", target)
        my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "slime1")
        return True
    return False


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_resent_count(self, 10)
    my.tp_set_attack_eater(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_damage_natural_attack_chance_d1000(self, 900)
    my.tp_set_damage_natural_attack_type(self, "gore")
    my.tp_set_damage_natural_dice(self, "1d8+3")
    my.tp_set_damage_poison_chance_d1000(self, 100)
    my.tp_set_damage_poison_dice(self, "2d8+2")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_distance_avoid(self, 5)
    my.tp_set_distance_jump(self, 2)
    my.tp_set_distance_mob_max(self, 5)
    my.tp_set_distance_vision(self, 5)
    my.tp_set_environ_avoids_fire(self, 10)
    my.tp_set_environ_avoids_poison(self, 100)
    my.tp_set_environ_avoids_water(self, 100)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "4d15+4")
    my.tp_set_hunger_clock_tick_frequency(self, 50)
    my.tp_set_hunger_health_pct(self, 95)
    my.tp_set_hunger_is_insatiable(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_fire_at(self, True)
    my.tp_set_is_able_to_jump_attack_chance_d1000(self, 800)
    my.tp_set_is_able_to_jump_attack(self, True)
    my.tp_set_is_able_to_jump_onto_chance_d1000(self, 100)
    my.tp_set_is_able_to_jump_onto(self, True)
    my.tp_set_is_able_to_jump_randomly_chance_d1000(self, 20)
    my.tp_set_is_able_to_jump(self, True)
    my.tp_set_is_able_to_jump_without_tiring(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_able_to_tire(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_bleeder(self, True)
    my.tp_set_is_breather(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_food_eater(self, True)
    my.tp_set_is_green_blooded(self, True)
    my.tp_set_is_heavy(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_spiderwebs(self, True)
    my.tp_set_is_living(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meat_eater(self, True)
    my.tp_set_is_monst_class_b(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_poisonous_danger_level(self, 2)  # danger level
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_spider(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_long_text_description(self, "An enormous spider. Ichor drips from its glistening fangs. Watch out for its web and poisonous bite.")
    my.tp_set_monst_size(self, my.MONST_SIZE_GIANT)
    my.tp_set_noise_decibels_hearing(self, 0)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_nutrition_dice(self, "1d6")
    my.tp_set_on_born_do(self, "me.on_born()")
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_miss_do(self, "me.on_you_miss_do()")
    my.tp_set_on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stamina(self, 100)
    my.tp_set_stat_con(self, 12)
    my.tp_set_stat_def(self, 14)
    my.tp_set_stat_dex(self, 16)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 14)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A giant spider.")
    my.tp_set_text_hits(self, "bites")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 150
    my.tp_set_tile(self, "spider_giant.1", delay_ms=delay)
    my.tp_set_tile(self, "spider_giant.2", delay_ms=delay)
    my.tp_set_tile(self, "spider_giant.3", delay_ms=delay)
    my.tp_set_tile(self, "spider_giant.4", delay_ms=delay)
    my.tp_set_tile(self, "spider_giant.5", delay_ms=delay)
    my.tp_set_tile(self, "spider_giant.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="spider_giant", text_name="giant spider")


init()
