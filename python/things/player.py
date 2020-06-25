import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(20)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_change_levels(True)
    x.set_is_active(True)
    x.set_is_attack_shove(True)
    x.set_is_attackable(True)
    x.set_is_bleeder(True)
    x.set_is_combustible(True)
    x.set_is_corpse_on_death(True)
    x.set_is_fire_hater(100)
    x.set_is_interesting(True)
    x.set_is_jumper(True)
    x.set_is_jumper_distance(2)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat(True)
    x.set_is_movable(True)
    x.set_is_player(True)
    x.set_is_shovable(True)
    x.set_stats_attack_dice("1d1+1")
    x.set_stats_defence(3)
    x.set_stats_health_hunger_pct(5)
    x.set_stats_health_initial(100)
    x.set_stats_health_starving_pct(5)
    x.set_stats_move_speed_ms(75)
    x.set_stats_strength(10)
    x.set_text_a_or_an("the");
    x.set_text_hits("hits");
    x.set_tick_rate_tenths(1)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 550
    x.set_tile(tile=name + ".1", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_left=True, is_moving=True,
               delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_up=True, is_moving=True,
               delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_down=True, is_moving=True,
               delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_right=True, is_moving=True,
               delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)

    x.set_tile(tile=name + ".dead", is_dead=True)

    x.update()

def init():
    tp_init(name="player1", text_name="noble warrior")

init()
