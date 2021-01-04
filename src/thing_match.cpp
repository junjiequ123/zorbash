//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include "my_main.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "slre.h"

bool Thing::match (const std::string& what)
{
    if (strisregexp(what.c_str())) {
        struct slre slre;
        if (slre_compile(&slre, what.c_str())) {
            auto name = short_text_name();
            if (slre_match(&slre, name.c_str(), name.size(), 0 /* captures */)) {
                return true;
            }
        }
	return false;
    }

    if (is_able_to_change_levels() && (what == "is_able_to_change_levels")) {
        return true;
    }
    if (is_acid() && (what == "is_acid")) {
        return true;
    }
    if (is_acid_dweller() && (what == "is_acid_dweller")) {
        return true;
    }
    if (is_acid_hater() && (what == "is_acid_hater")) {
        return true;
    }
    if (is_active() && (what == "is_active")) {
        return true;
    }
    if (is_alive_monst() && (what == "is_alive_monst")) {
        return true;
    }
    if (is_attack_eater() && (what == "is_attack_eater")) {
        return true;
    }
    if (is_attack_lunge() && (what == "is_attack_lunge")) {
        return true;
    }
    if (is_attack_shove() && (what == "is_attack_shove")) {
        return true;
    }
    if (is_attack_shove_chance_d1000() && (what == "is_attack_shove_chance_d1000")) {
        return true;
    }
    if (is_attackable_by_monst() && (what == "is_attackable_by_monst")) {
        return true;
    }
    if (is_attackable_by_player() && (what == "is_attackable_by_player")) {
        return true;
    }
    if (is_bag() && (what == "is_bag")) {
        return true;
    }
    if (is_bleeder() && (what == "is_bleeder")) {
        return true;
    }
    if (is_blood() && (what == "is_blood")) {
        return true;
    }
    if (is_blood_splatter() && (what == "is_blood_splatter")) {
        return true;
    }
    if (is_chasm() && (what == "is_chasm")) {
        return true;
    }
    if (is_collect_as_keys() && (what == "is_collect_as_keys")) {
        return true;
    }
    if (is_collectable() && (what == "is_collectable")) {
        return true;
    }
    if (is_combustible() && (what == "is_combustible")) {
        return true;
    }
    if (is_corpse() && (what == "is_corpse")) {
        return true;
    }
    if (is_corridor() && (what == "is_corridor")) {
        return true;
    }
    if (is_cursor() && (what == "is_cursor")) {
        return true;
    }
    if (is_cursor_can_hover_over() && (what == "is_cursor_can_hover_over")) {
        return true;
    }
    if (is_cursor_can_hover_over_but_needs_double_click() && (what == "is_cursor_can_hover_over_but_needs_double_click")) {
        return true;
    }
    if (is_cursor_path() && (what == "is_cursor_path")) {
        return true;
    }
    if (is_dead_on_shove() && (what == "is_dead_on_shove")) {
        return true;
    }
    if (is_deep_water() && (what == "is_deep_water")) {
        return true;
    }
    if (is_dirt() && (what == "is_dirt")) {
        return true;
    }
    if (is_door() && (what == "is_door")) {
        return true;
    }
    if (is_double_damage_from_acid() && (what == "is_double_damage_from_acid")) {
        return true;
    }
    if (is_double_damage_from_fire() && (what == "is_double_damage_from_fire")) {
        return true;
    }
    if (is_double_damage_from_water() && (what == "is_double_damage_from_water")) {
        return true;
    }
    if (is_droppable() && (what == "is_droppable")) {
        return true;
    }
    if (is_entrance() && (what == "is_entrance")) {
        return true;
    }
    if (is_ethereal() && (what == "is_ethereal")) {
        return true;
    }
    if (is_exit() && (what == "is_exit")) {
        return true;
    }
    if (is_explosion() && (what == "is_explosion")) {
        return true;
    }
    if (is_fire() && (what == "is_fire")) {
        return true;
    }
    if (is_fire_hater() && (what == "is_fire_hater")) {
        return true;
    }
    if (is_flammable() && (what == "is_flammable")) {
        return true;
    }
    if (is_floating() && (what == "is_floating")) {
        return true;
    }
    if (is_floor() && (what == "is_floor")) {
        return true;
    }
    if (is_floor_deco() && (what == "is_floor_deco")) {
        return true;
    }
    if (is_food() && (what == "is_food")) {
        return true;
    }
    if (is_generator() && (what == "is_generator")) {
        return true;
    }
    if (is_gold() && (what == "is_gold")) {
        return true;
    }
    if (is_hazard() && (what == "is_hazard")) {
        return true;
    }
    if (is_hunger_insatiable() && (what == "is_hunger_insatiable")) {
        return true;
    }
    if (is_intelligent() && (what == "is_intelligent")) {
        return true;
    }
    if (is_interesting() && (what == "is_interesting")) {
        return true;
    }
    if (is_item() && (what == "is_item")) {
        return true;
    }
    if (is_item_collected_as_gold() && (what == "is_item_collected_as_gold")) {
        return true;
    }
    if (is_item_eater() && (what == "is_item_eater")) {
        return true;
    }
    if (is_item_not_stackable() && (what == "is_item_not_stackable")) {
        return true;
    }
    if (is_jelly() && (what == "is_jelly")) {
        return true;
    }
    if (is_jelly_baby() && (what == "is_jelly_baby")) {
        return true;
    }
    if (is_jelly_baby_eater() && (what == "is_jelly_baby_eater")) {
        return true;
    }
    if (is_jelly_eater() && (what == "is_jelly_eater")) {
        return true;
    }
    if (is_jelly_parent() && (what == "is_jelly_parent")) {
        return true;
    }
    if (is_jumper() && (what == "is_jumper")) {
        return true;
    }
    if (is_jumper_chance_d1000() && (what == "is_jumper_chance_d1000")) {
        return true;
    }
    if (is_jumper_distance() && (what == "is_jumper_distance")) {
        return true;
    }
    if (is_jumper_on_low_hp_chance_d1000() && (what == "is_jumper_on_low_hp_chance_d1000")) {
        return true;
    }
    if (is_key() && (what == "is_key")) {
        return true;
    }
    if (is_killed_on_hit_or_miss() && (what == "is_killed_on_hit_or_miss")) {
        return true;
    }
    if (is_killed_on_hitting() && (what == "is_killed_on_hitting")) {
        return true;
    }
    if (is_lava() && (what == "is_lava")) {
        return true;
    }
    if (is_light_blocker() && (what == "is_light_blocker")) {
        return true;
    }
    if (is_light_strength() && (what == "is_light_strength")) {
        return true;
    }
    if (is_loggable_for_important_stuff() && (what == "is_loggable_for_important_stuff")) {
        return true;
    }
    if (is_loggable_for_unimportant_stuff() && (what == "is_loggable_for_unimportant_stuff")) {
        return true;
    }
    if (is_meat() && (what == "is_meat")) {
        return true;
    }
    if (is_meat_eater() && (what == "is_meat_eater")) {
        return true;
    }
    if (is_monst() && (what == "is_monst")) {
        return true;
    }
    if (is_movable() && (what == "is_movable")) {
        return true;
    }
    if (is_movement_blocking_hard() && (what == "is_movement_blocking_hard")) {
        return true;
    }
    if (is_movement_blocking_soft() && (what == "is_movement_blocking_soft")) {
        return true;
    }
    if (is_msg() && (what == "is_msg")) {
        return true;
    }
    if (is_no_tile() && (what == "is_no_tile")) {
        return true;
    }
    if (is_player() && (what == "is_player")) {
        return true;
    }
    if (is_potion() && (what == "is_potion")) {
        return true;
    }
    if (is_potion_eater() && (what == "is_potion_eater")) {
        return true;
    }
    if (is_projectile() && (what == "is_projectile")) {
        return true;
    }
    if (is_removable_if_out_of_slots() && (what == "is_removable_if_out_of_slots")) {
        return true;
    }
    if (is_resurrectable() && (what == "is_resurrectable")) {
        return true;
    }
    if (is_ripple() && (what == "is_ripple")) {
        return true;
    }
    if (is_rock() && (what == "is_rock")) {
        return true;
    }
    if (is_rrr1() && (what == "is_rrr1")) {
        return true;
    }
    if (is_rrr10() && (what == "is_rrr10")) {
        return true;
    }
    if (is_rrr11() && (what == "is_rrr11")) {
        return true;
    }
    if (is_rrr12() && (what == "is_rrr12")) {
        return true;
    }
    if (is_rrr13() && (what == "is_rrr13")) {
        return true;
    }
    if (is_rrr14() && (what == "is_rrr14")) {
        return true;
    }
    if (is_rrr15() && (what == "is_rrr15")) {
        return true;
    }
    if (is_rrr16() && (what == "is_rrr16")) {
        return true;
    }
    if (is_rrr17() && (what == "is_rrr17")) {
        return true;
    }
    if (is_rrr18() && (what == "is_rrr18")) {
        return true;
    }
    if (is_rrr19() && (what == "is_rrr19")) {
        return true;
    }
    if (is_rrr2() && (what == "is_rrr2")) {
        return true;
    }
    if (is_rrr20() && (what == "is_rrr20")) {
        return true;
    }
    if (is_rrr21() && (what == "is_rrr21")) {
        return true;
    }
    if (is_rrr22() && (what == "is_rrr22")) {
        return true;
    }
    if (is_rrr23() && (what == "is_rrr23")) {
        return true;
    }
    if (is_rrr24() && (what == "is_rrr24")) {
        return true;
    }
    if (is_rrr25() && (what == "is_rrr25")) {
        return true;
    }
    if (is_rrr26() && (what == "is_rrr26")) {
        return true;
    }
    if (is_rrr27() && (what == "is_rrr27")) {
        return true;
    }
    if (is_rrr28() && (what == "is_rrr28")) {
        return true;
    }
    if (is_rrr29() && (what == "is_rrr29")) {
        return true;
    }
    if (is_rrr3() && (what == "is_rrr3")) {
        return true;
    }
    if (is_rrr30() && (what == "is_rrr30")) {
        return true;
    }
    if (is_rrr31() && (what == "is_rrr31")) {
        return true;
    }
    if (is_rrr32() && (what == "is_rrr32")) {
        return true;
    }
    if (is_rrr33() && (what == "is_rrr33")) {
        return true;
    }
    if (is_rrr34() && (what == "is_rrr34")) {
        return true;
    }
    if (is_rrr35() && (what == "is_rrr35")) {
        return true;
    }
    if (is_rrr36() && (what == "is_rrr36")) {
        return true;
    }
    if (is_rrr37() && (what == "is_rrr37")) {
        return true;
    }
    if (is_rrr38() && (what == "is_rrr38")) {
        return true;
    }
    if (is_rrr39() && (what == "is_rrr39")) {
        return true;
    }
    if (is_rrr4() && (what == "is_rrr4")) {
        return true;
    }
    if (is_rrr40() && (what == "is_rrr40")) {
        return true;
    }
    if (is_rrr41() && (what == "is_rrr41")) {
        return true;
    }
    if (is_rrr42() && (what == "is_rrr42")) {
        return true;
    }
    if (is_rrr43() && (what == "is_rrr43")) {
        return true;
    }
    if (is_rrr44() && (what == "is_rrr44")) {
        return true;
    }
    if (is_rrr45() && (what == "is_rrr45")) {
        return true;
    }
    if (is_rrr46() && (what == "is_rrr46")) {
        return true;
    }
    if (is_rrr47() && (what == "is_rrr47")) {
        return true;
    }
    if (is_food_eater() && (what == "is_food_eater")) {
        return true;
    }
    if (is_item_effect_max_radius() && (what == "is_item_effect_max_radius")) {
        return true;
    }
    if (is_rrr5() && (what == "is_rrr5")) {
        return true;
    }
    if (is_item_effect_min_radius() && (what == "is_item_effect_min_radius")) {
        return true;
    }
    if (is_critical_to_level() && (what == "is_critical_to_level")) {
        return true;
    }
    if (is_able_to_fall() && (what == "is_able_to_fall")) {
        return true;
    }
    if (is_temporary_bag() && (what == "is_temporary_bag")) {
        return true;
    }
    if (is_chasm() && (what == "is_chasm")) {
        return true;
    }
    if (is_rrr6() && (what == "is_rrr6")) {
        return true;
    }
    if (is_rrr7() && (what == "is_rrr7")) {
        return true;
    }
    if (is_rrr8() && (what == "is_rrr8")) {
        return true;
    }
    if (is_rrr9() && (what == "is_rrr9")) {
        return true;
    }
    if (is_secret_door() && (what == "is_secret_door")) {
        return true;
    }
    if (is_shovable() && (what == "is_shovable")) {
        return true;
    }
    if (is_shown_on_leftbar() && (what == "is_shown_on_leftbar")) {
        return true;
    }
    if (is_shown_uniquely_on_leftbar() && (what == "is_shown_uniquely_on_leftbar")) {
        return true;
    }
    if (is_smoke() && (what == "is_smoke")) {
        return true;
    }
    if (is_stamina_check() && (what == "is_stamina_check")) {
        return true;
    }
    if (is_steal_item_chance_d1000() && (what == "is_steal_item_chance_d1000")) {
        return true;
    }
    if (is_throwable() && (what == "is_throwable")) {
        return true;
    }
    if (is_torch() && (what == "is_torch")) {
        return true;
    }
    if (is_treasure() && (what == "is_treasure")) {
        return true;
    }
    if (is_treasure_class_a() && (what == "is_treasure_class_a")) {
        return true;
    }
    if (is_treasure_class_b() && (what == "is_treasure_class_b")) {
        return true;
    }
    if (is_treasure_class_c() && (what == "is_treasure_class_c")) {
        return true;
    }
    if (is_treasure_eater() && (what == "is_treasure_eater")) {
        return true;
    }
    if (is_undead() && (what == "is_undead")) {
        return true;
    }
    if (is_usable() && (what == "is_usable")) {
        return true;
    }
    if (is_wall() && (what == "is_wall")) {
        return true;
    }
    if (is_wall_deco() && (what == "is_wall_deco")) {
        return true;
    }
    if (is_water() && (what == "is_water")) {
        return true;
    }
    if (is_water_dweller() && (what == "is_water_dweller")) {
        return true;
    }
    if (is_water_hater() && (what == "is_water_hater")) {
        return true;
    }
    if (is_weapon() && (what == "is_weapon")) {
        return true;
    }
    if (is_weapon_wielder() && (what == "is_weapon_wielder")) {
        return true;
    }

    return (what == short_text_name());
}
