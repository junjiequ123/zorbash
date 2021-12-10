import my
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_environ_avoids_fire(100)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_food(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_organic(True)
    mytp.set_is_throwable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_usable(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Chocolate frogs. The food of Gods. May seem out of place in a dungeon and you'd be correct. It is rumored a helpful god left them here for brave adventurers to assist them on their path. Often found in a purple wrapper. Almost looks too good to eat.")
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("50+1d100")
    mytp.set_rarity(my.RARITY_UNCOMMON)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=brown$The food of the Gods: a chocolate frog.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, is_hp_100_percent=True)
    mytp.update()

def init():
    tp_init(name="food_frog", text_name="chocolate frog", short_text_name="choc frog")

init()