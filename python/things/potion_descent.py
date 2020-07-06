import zx
import tp


def potion_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_collectable(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(2)
    x.set_is_movable(True)
    x.set_is_potion(True)
    x.set_is_sidebar_item(True)
    x.set_light_color("cyan")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a");
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    x.set_tile(tile=name + ".1", delay_ms=1000)
    x.set_tile(tile=name + ".2", delay_ms=1000)
    x.set_tile(tile=name + ".3", delay_ms=1000)

    x.update()

def init():
    potion_init(name="potion_blue", text_name="potion of descent")

init()
