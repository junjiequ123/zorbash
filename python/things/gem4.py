import zx
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_collision_circle(True)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_small_shadow_caster(True)
    mytp.set_gold_value_dice("1d200")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_item_collected_as_gold(True)
    mytp.set_is_shown_on_leftbar(True)
    mytp.set_is_treasure(True)
    mytp.set_is_treasure_class_b(True)
    mytp.set_long_text_description("The stone of loyalty. Can't be that loyal as someone left it lying here. Best to pick it up for safe keeping.")
    mytp.set_normal_placement_rules(True)
    mytp.set_rarity(zx.RARITY_UNCOMMON)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=green$Grass green emerald.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=2000)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=50)

    mytp.update()

def init():
    tp_init(name="gem_emerald", text_name="emerald")

init()
