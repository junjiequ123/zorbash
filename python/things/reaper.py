import zx
import tp

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_delay_after_moving_ms(100)
    x.set_ai_scent_distance(40)
    x.set_attack_living(True)
    x.set_attack_lunge(True)
    x.set_is_attackable_by_player(True)
    x.set_avoids_fire(100)
    x.set_avoids_water(100)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_damage_doubled_from_water(True)
    x.set_damage_melee_dice("1d6+6")
    x.set_gfx_anim_attack("scythe_swing")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(False)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(95)
    x.set_health_initial_dice("2d20+200")
    x.set_is_able_to_change_levels(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_combustible(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_fearless(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_intelligent(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_monst(True)
    x.set_is_moveable(True)
    x.set_is_resurrectable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_undead(True)
    x.set_long_text_description("A lesser reaper. You cannot kill what does not live!")
    x.set_modifier_attack(25)
    x.set_modifier_constitution(25)
    x.set_modifier_defence(25)
    x.set_modifier_strength(25)
    x.set_monst_size(zx.MONST_SIZE_NORMAL)
    x.set_move_speed_ms(300)
    x.set_normal_placement_rules(True)
    x.set_on_death_is_corpse(True)
    x.set_rarity(zx.RARITY_VERY_RARE)
    x.set_resurrect_dice("1d10+30")
    x.set_text_a_or_an("a");
    x.set_text_description("A lesser reaper. Death incarnate.")
    x.set_text_hits("claws");
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 1000
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)

    delay = 200
    x.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    x.set_tile(tile=name + ".5.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.dead", is_resurrecting=True, is_end_of_anim=True, is_alive_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="reaper", text_name="reaper")

init()

