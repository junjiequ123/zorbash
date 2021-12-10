import my
import tp


def tp_init(name):
    mytp = tp.Tp(name, "bones and skin and stuff")
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bones(True)
    mytp.set_is_loggable(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Some poor creature's remnants.")
    mytp.set_z_depth(my.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name)
    mytp.update()

def init():
    tp_init(name="bones.1")
    tp_init(name="bones.2")
    tp_init(name="bones.3")
    tp_init(name="bones.4")
    tp_init(name="bones.5")
    tp_init(name="bones.6")

init()