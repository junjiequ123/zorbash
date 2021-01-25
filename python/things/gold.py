import zx
import tp


def gold_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_bounce_always(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_gold_value_dice("1d6")
    x.set_is_able_to_fall(True)
    x.set_is_collectable(True)
    x.set_is_gold(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_attackable(True)
    x.set_is_auto_collect_item(True)
    x.set_is_item_collected_as_gold(True)
    x.set_attackable(True)
    x.set_is_light_strength(1)
    x.set_is_moveable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_treasure(True)
    x.set_attackable(True)
    x.set_is_treasure_class_a(True)
    x.set_attackable(True)
    x.set_light_color("yellow")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("an");
    x.set_text_description("Some gold goins")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".7", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".8", is_dir_none=True, delay_ms=50)

    x.update()

def init():
    gold_init(name="gold", text_name="gold")

init()