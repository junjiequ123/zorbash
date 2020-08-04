import zx
import tp

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_is_attack_blood(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_removable_if_out_of_slots(True)
    x.set_text_a_or_an("a");
    x.set_text_description("An artwork comprised mainly of blood")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 20
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay)
    x.set_tile(tile=name + ".8", delay_ms=delay)
    x.set_tile(tile=name + ".9", delay_ms=delay)
    x.set_tile(tile=name + ".10", delay_ms=delay)
    x.set_tile(tile=name + ".11", delay_ms=delay)
    x.set_tile(tile=name + ".12", delay_ms=delay)
    x.set_tile(tile=name + ".13", delay_ms=delay)
    x.set_tile(tile=name + ".14", delay_ms=delay, is_end_of_anim=True, is_dead_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="attack_blood1", text_name="blood splatter")

init()