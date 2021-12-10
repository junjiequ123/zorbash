import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_capacity_height(8)
    mytp.set_capacity_width(8)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item_container(True)
    mytp.set_is_bag_item_not_stackable(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_burnable(True)
    mytp.set_is_carrier_of_treasure_class_a(True)
    mytp.set_is_carrier_of_treasure_class_b(True)
    mytp.set_is_carrier_of_treasure_class_c(True)
    mytp.set_is_collectable(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_hittable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item_carrier(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_metal(True)
    mytp.set_is_moveable(True)
    mytp.set_is_openable(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure_type_chest(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_wooden(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("A small treasure chest.")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_drop_all_items(True)
    mytp.set_on_death_is_open(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A small treasure chest.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile="chest1", delay_ms=1000)
    mytp.set_tile(tile=name + ".open", is_open=True)
    mytp.update()


def init():
    tp_init(name="chest1", text_name="small treasure chest")


init()
