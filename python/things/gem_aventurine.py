import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_gold_value_dice("1d50")
    x.set_is_able_to_fall(True)
    x.set_is_collectable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_attackable(True)
    x.set_is_item_collected_as_gold(True)
    x.set_attackable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_treasure(True)
    x.set_attackable(True)
    x.set_is_treasure_class_b(True)
    x.set_attackable(True)
    x.set_is_described_when_hovering_over(True)
    x.set_long_text_description("If you are need of luck, adventurine is the stone for you. It has a few drops of blood on it, ignore those. You will be more lucky.")
    x.set_normal_placement_rules(True)
    x.set_rarity(zx.RARITY_COMMON)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=forestgreen$Some adventurine, the luckiest stone")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=2000)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=50)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=50)

    x.update()

def init():
    tp_init(name="gem_aventurine", text_name="aventurine") # good luck

init()