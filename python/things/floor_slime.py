import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_animated_can_vflip(True)
    x.set_gfx_show_outlined(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_removable_if_out_of_slots(True)
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a");
    x.set_text_description("An artwork comprised mainly of slime")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile="attack_slime.14")

    x.update()

def init():
    tp_init(name="floor_slime", text_name="slime splatter")

init()