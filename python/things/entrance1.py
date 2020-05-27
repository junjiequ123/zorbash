import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_text_a_or_an("the");
    x.set_is_entrance(True)
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(4)
    x.set_light_color("yellow")
    x.set_normal_placement_rules(True)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    delay = 1000
    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="entrance1", text_name="dungeon entrance")

init()
