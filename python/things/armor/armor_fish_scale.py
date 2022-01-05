import my
import tp

mytp = None


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_aquatic")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_aquatic")


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.topcon("The scale armor glows.")
    my.thing_incr_stat_def(me, 2)


def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_break_chance_d10000(1000)
    mytp.set_enchant_max(10)
    mytp.set_equip_carry_anim("armor_fish_scale_carry")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gold_value_dice("50")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_armor(True)
    mytp.set_is_auto_equipped(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meltable(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_is_treasure_type(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Scale mail armor composed of lots of little fish shaped scales. Smells a bit fishy too. You might actually be wearing a fish.")
    mytp.set_melting_chance_d1000(2)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_enchant_do("me.on_enchant()")
    mytp.set_on_equip_do("me.on_equip()")
    mytp.set_on_unequip_do("me.on_unequip()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stat_def(12)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Fish scale mail armor.")
    mytp.set_text_enchant("+2 AC")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name)

    mytp.update()


def init():
    tp_init(
        name="armor_fish_scale",
        text_name="fish scale armor",
        short_text_name="fish scale armor",
    )


init()