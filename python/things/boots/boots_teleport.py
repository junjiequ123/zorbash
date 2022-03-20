import my
import tp

self = None


def on_equip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your feet are nice and warm!")


def on_unequip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your feet are cold again!")


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The boots become a bit less squeaky.")
    my.thing_noise_incr(me, -10)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.equip_carry_anim(self, "boots_teleport_carry")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "250")
    my.is_able_to_fall(self, True)
    my.is_boots(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.noise_additional_on_teleporting(self, 50)
    my.noise_additional_on_jumping(self, 50)
    my.noise_on_dropping(self, 50)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_a(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_burnable(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.distance_teleport(self, 10)
    my.long_text_description(self, "Boots on uncontrolled teleport. Sometimes useful, these squeaky boots will randomly teleport you up to 10 tiles away when used. This may be good or bad depending on your situation.")
    my.stat_dex_mod(self, 1)
    my.stat_def_mod(self, 1)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_COMMON)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Boots of teleport.")
    my.text_enchant(self, "-10 decibels")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="boots_teleport",
        text_name="boots of teleport",
        short_text_name="boots of teleport",
    )


init()