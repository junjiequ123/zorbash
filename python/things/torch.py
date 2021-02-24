import zx
import tp


def tp_init(name, text_name, tiles=[]):
    x = tp.Tp(name, text_name)
    x.set_ai_obstacle(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True) # for pushing and falling
    x.set_is_combustible(True)
    x.set_is_dead_on_shove(True)
    x.set_is_fire(True)
    x.set_is_flammable(True)
    x.set_is_floor_deco(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(2)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_movement_blocking_soft(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_shown_uniquely_on_leftbar(True)
    x.set_is_torch(True)
    x.set_light_color("yellow")
    x.set_normal_placement_rules(True)
    x.set_on_death_is_corpse(True)
    x.set_spawn_on_shoved("fire")
    x.set_text_a_or_an("a");
    x.set_text_description("A beacon of light in this blighted place.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay=100
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.set_tile(tile=name + ".dead", is_dead=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="torch1", text_name="torch",
            tiles=[
                "torch1.1",
                "torch1.2",
                "torch1.3",
                "torch1.4",
                "torch1.5",
                "torch1.6",
                "torch1.7",
                "torch1.8",
                "torch1.9",
                "torch1.10",
                "torch1.11",
                "torch1.12",
                "torch1.13",
                "torch1.14",
                "torch1.15",
                "torch1.16",
                "torch1.17",
                "torch1.18",
                "torch1.19",
                "torch1.20",
                "torch1.21",
                "torch1.22",
                "torch1.23",
                "torch1.24",
                "torch1.25",
                "torch1.26",
                "torch1.27",
                "torch1.28",
                "torch1.29",
                "torch1.30",
                "torch1.31",
                "torch1.32",
                "torch1.33",
                "torch1.34",
                "torch1.35",
                "torch1.36",
                "torch1.37",
                ])
init()
