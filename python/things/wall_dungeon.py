import zx
import tp


def tp_init(name,
            tiles=[],
            left1_tiles=[],
            right1_tiles=[],
            top1_tiles=[],
            bot1_tiles=[],
            tl1_tiles=[],
            tr1_tiles=[],
            bl1_tiles=[],
            br1_tiles=[],
            left2_tiles=[],
            right2_tiles=[],
            top2_tiles=[],
            bot2_tiles=[],
            tl2_tiles=[],
            tr2_tiles=[],
            bl2_tiles=[],
            br2_tiles=[]):

    x = tp.Tp(name)
    x.set_ai_obstacle(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_shown_in_bg(True)
    x.set_is_able_to_fall(False)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_interesting(False)
    x.set_is_light_blocker(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_movement_blocking_hard(True)
    x.set_is_wall(True)
    x.set_is_wall_dungeon(True)
    x.set_text_a_or_an("a");
    x.set_text_description("A moss covered wall.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    if tiles is not None:
        for t in tiles:
            x.set_tile(t)
    else:
        x.set_tile(tile=name)

    if left1_tiles is not None:
        for t in left1_tiles:
            x.set_left1_tile(t)
    else:
        x.set_left1_tile(left1_tile=name)

    if right1_tiles is not None:
        for t in right1_tiles:
            x.set_right1_tile(t)
    else:
        x.set_right1_tile(right1_tile=name)

    if top1_tiles is not None:
        for t in top1_tiles:
            x.set_top1_tile(t)
    else:
        x.set_top1_tile(top1_tile=name)

    if bot1_tiles is not None:
        for t in bot1_tiles:
            x.set_bot1_tile(t)
    else:
        x.set_bot1_tile(bot1_tile=name)

    if tl1_tiles is not None:
        for t in tl1_tiles:
            x.set_tl1_tile(t)
    else:
        x.set_tl1_tile(tl1_tile=name)

    if tr1_tiles is not None:
        for t in tr1_tiles:
            x.set_tr1_tile(t)
    else:
        x.set_tr1_tile(tr1_tile=name)

    if bl1_tiles is not None:
        for t in bl1_tiles:
            x.set_bl1_tile(t)
    else:
        x.set_bl1_tile(bl1_tile=name)

    if br1_tiles is not None:
        for t in br1_tiles:
            x.set_br1_tile(t)
    else:
        x.set_br1_tile(br1_tile=name)

    if left2_tiles is not None:
        for t in left2_tiles:
            x.set_left2_tile(t)
    else:
        x.set_left2_tile(left2_tile=name)

    if right2_tiles is not None:
        for t in right2_tiles:
            x.set_right2_tile(t)
    else:
        x.set_right2_tile(right2_tile=name)

    if top2_tiles is not None:
        for t in top2_tiles:
            x.set_top2_tile(t)
    else:
        x.set_top2_tile(top2_tile=name)

    if bot2_tiles is not None:
        for t in bot2_tiles:
            x.set_bot2_tile(t)
    else:
        x.set_bot2_tile(bot2_tile=name)

    if tl2_tiles is not None:
        for t in tl2_tiles:
            x.set_tl2_tile(t)
    else:
        x.set_tl2_tile(tl2_tile=name)

    if tr2_tiles is not None:
        for t in tr2_tiles:
            x.set_tr2_tile(t)
    else:
        x.set_tr2_tile(tr2_tile=name)

    if bl2_tiles is not None:
        for t in bl2_tiles:
            x.set_bl2_tile(t)
    else:
        x.set_bl2_tile(bl2_tile=name)

    if br2_tiles is not None:
        for t in br2_tiles:
            x.set_br2_tile(t)
    else:
        x.set_br2_tile(br2_tile=name)

    x.update()

def init():
    tp_init(name="wall_dungeon.1",
            tiles=[       "wall_dungeon.1.1", "wall_dungeon.1.2", "wall_dungeon.1.3", "wall_dungeon.1.4",
                          "wall_dungeon.1.5", "wall_dungeon.1.6", "wall_dungeon.1.7", "wall_dungeon.1.8",
                          "wall_dungeon.1.9", "wall_dungeon.1.10", "wall_dungeon.1.11", "wall_dungeon.1.12",
                          "wall_dungeon.1.13", "wall_dungeon.1.14", "wall_dungeon.1.15", "wall_dungeon.1.16",
                          "wall_dungeon.1.17", "wall_dungeon.1.18", "wall_dungeon.1.19", ],
            left1_tiles=[ "wall_deco1.left.1", "wall_deco1.left.2",
                          "wall_deco1.left.3", "wall_deco1.left.4",
                          "wall_deco1.left.5", "wall_deco1.left.6", ],
            right1_tiles=["wall_deco1.right.1", "wall_deco1.right.2",
                          "wall_deco1.right.3", "wall_deco1.right.4",
                          "wall_deco1.right.5", "wall_deco1.right.6", ],
            top1_tiles=[  "wall_deco1.top.1", "wall_deco1.top.2",
                          "wall_deco1.top.3", "wall_deco1.top.4",
                          "wall_deco1.top.5", "wall_deco1.top.6",
                          "wall_deco1.top.7", ],
            bot1_tiles=[  "wall_deco1.bot.1", "wall_deco1.bot.2",
                          "wall_deco1.bot.3", "wall_deco1.bot.4",
                          "wall_deco1.bot.5", "wall_deco1.bot.6",
                          "wall_deco1.bot.7", ],
            tl1_tiles=[   "wall_deco1.tl.1", "wall_deco1.tl.2",
                          "wall_deco1.tl.3", "wall_deco1.tl.4",
                          "wall_deco1.tl.5", "wall_deco1.tl.6", ],
            tr1_tiles=[   "wall_deco1.tr.1", "wall_deco1.tr.2",
                          "wall_deco1.tr.3", "wall_deco1.tr.4",
                          "wall_deco1.tr.5", "wall_deco1.tr.6", ],
            br1_tiles=[   "wall_deco1.br.1", "wall_deco1.br.2",
                          "wall_deco1.br.3", "wall_deco1.br.4",
                          "wall_deco1.br.5", "wall_deco1.br.6", ],
            bl1_tiles=[   "wall_deco1.bl.1", "wall_deco1.bl.2",
                          "wall_deco1.bl.3", "wall_deco1.bl.4",
                          "wall_deco1.bl.5", "wall_deco1.bl.6", ],
            left2_tiles=[ "wall_shadow_deco1.left.1", "wall_shadow_deco1.left.2",
                          "wall_shadow_deco1.left.3", "wall_shadow_deco1.left.4",
                          "wall_shadow_deco1.left.5", "wall_shadow_deco1.left.6", ],
            right2_tiles=["wall_shadow_deco1.right.1", "wall_shadow_deco1.right.2",
                          "wall_shadow_deco1.right.3", "wall_shadow_deco1.right.4",
                          "wall_shadow_deco1.right.5", "wall_shadow_deco1.right.6", ],
            top2_tiles=[  "wall_shadow_deco1.top.1", "wall_shadow_deco1.top.2",
                          "wall_shadow_deco1.top.3", "wall_shadow_deco1.top.4",
                          "wall_shadow_deco1.top.5", "wall_shadow_deco1.top.6",
                          "wall_shadow_deco1.top.7", ],
            bot2_tiles=[  "wall_shadow_deco1.bot.1", "wall_shadow_deco1.bot.2",
                          "wall_shadow_deco1.bot.3", "wall_shadow_deco1.bot.4",
                          "wall_shadow_deco1.bot.5", "wall_shadow_deco1.bot.6",
                          "wall_shadow_deco1.bot.7", ],
            tl2_tiles=[   "wall_shadow_deco1.tl.1", "wall_shadow_deco1.tl.2",
                          "wall_shadow_deco1.tl.3", "wall_shadow_deco1.tl.4",
                          "wall_shadow_deco1.tl.5", "wall_shadow_deco1.tl.6", ],
            tr2_tiles=[   "wall_shadow_deco1.tr.1", "wall_shadow_deco1.tr.2",
                          "wall_shadow_deco1.tr.3", "wall_shadow_deco1.tr.4",
                          "wall_shadow_deco1.tr.5", "wall_shadow_deco1.tr.6", ],
            br2_tiles=[   "wall_shadow_deco1.br.1", "wall_shadow_deco1.br.2",
                          "wall_shadow_deco1.br.3", "wall_shadow_deco1.br.4",
                          "wall_shadow_deco1.br.5", "wall_shadow_deco1.br.6", ],
            bl2_tiles=[   "wall_shadow_deco1.bl.1", "wall_shadow_deco1.bl.2",
                          "wall_shadow_deco1.bl.3", "wall_shadow_deco1.bl.4",
                          "wall_shadow_deco1.bl.5", "wall_shadow_deco1.bl.6", ],
            )

    tp_init(name="wall_dungeon.2",
            tiles=[       "wall_dungeon.2.1", "wall_dungeon.2.2", "wall_dungeon.2.3", "wall_dungeon.2.4",
                          "wall_dungeon.2.5", "wall_dungeon.2.6", "wall_dungeon.2.7", "wall_dungeon.2.8",
                          "wall_dungeon.2.9", "wall_dungeon.2.10", "wall_dungeon.2.11", "wall_dungeon.2.12",
                          "wall_dungeon.2.13", "wall_dungeon.2.14", "wall_dungeon.2.15", "wall_dungeon.2.16",
                          "wall_dungeon.2.17", "wall_dungeon.2.18", "wall_dungeon.2.19", ],
            left1_tiles=[ "wall_deco1.left.1", "wall_deco1.left.2",
                          "wall_deco1.left.3", "wall_deco1.left.4",
                          "wall_deco1.left.5", "wall_deco1.left.6", ],
            right1_tiles=["wall_deco1.right.1", "wall_deco1.right.2",
                          "wall_deco1.right.3", "wall_deco1.right.4",
                          "wall_deco1.right.5", "wall_deco1.right.6", ],
            top1_tiles=[  "wall_deco1.top.1", "wall_deco1.top.2",
                          "wall_deco1.top.3", "wall_deco1.top.4",
                          "wall_deco1.top.5", "wall_deco1.top.6",
                          "wall_deco1.top.7", ],
            bot1_tiles=[  "wall_deco1.bot.1", "wall_deco1.bot.2",
                          "wall_deco1.bot.3", "wall_deco1.bot.4",
                          "wall_deco1.bot.5", "wall_deco1.bot.6",
                          "wall_deco1.bot.7", ],
            tl1_tiles=[   "wall_deco1.tl.1", "wall_deco1.tl.2",
                          "wall_deco1.tl.3", "wall_deco1.tl.4",
                          "wall_deco1.tl.5", "wall_deco1.tl.6", ],
            tr1_tiles=[   "wall_deco1.tr.1", "wall_deco1.tr.2",
                          "wall_deco1.tr.3", "wall_deco1.tr.4",
                          "wall_deco1.tr.5", "wall_deco1.tr.6", ],
            br1_tiles=[   "wall_deco1.br.1", "wall_deco1.br.2",
                          "wall_deco1.br.3", "wall_deco1.br.4",
                          "wall_deco1.br.5", "wall_deco1.br.6", ],
            bl1_tiles=[   "wall_deco1.bl.1", "wall_deco1.bl.2",
                          "wall_deco1.bl.3", "wall_deco1.bl.4",
                          "wall_deco1.bl.5", "wall_deco1.bl.6", ],
            left2_tiles=[ "wall_shadow_deco1.left.1", "wall_shadow_deco1.left.2",
                          "wall_shadow_deco1.left.3", "wall_shadow_deco1.left.4",
                          "wall_shadow_deco1.left.5", "wall_shadow_deco1.left.6", ],
            right2_tiles=["wall_shadow_deco1.right.1", "wall_shadow_deco1.right.2",
                          "wall_shadow_deco1.right.3", "wall_shadow_deco1.right.4",
                          "wall_shadow_deco1.right.5", "wall_shadow_deco1.right.6", ],
            top2_tiles=[  "wall_shadow_deco1.top.1", "wall_shadow_deco1.top.2",
                          "wall_shadow_deco1.top.3", "wall_shadow_deco1.top.4",
                          "wall_shadow_deco1.top.5", "wall_shadow_deco1.top.6",
                          "wall_shadow_deco1.top.7", ],
            bot2_tiles=[  "wall_shadow_deco1.bot.1", "wall_shadow_deco1.bot.2",
                          "wall_shadow_deco1.bot.3", "wall_shadow_deco1.bot.4",
                          "wall_shadow_deco1.bot.5", "wall_shadow_deco1.bot.6",
                          "wall_shadow_deco1.bot.7", ],
            tl2_tiles=[   "wall_shadow_deco1.tl.1", "wall_shadow_deco1.tl.2",
                          "wall_shadow_deco1.tl.3", "wall_shadow_deco1.tl.4",
                          "wall_shadow_deco1.tl.5", "wall_shadow_deco1.tl.6", ],
            tr2_tiles=[   "wall_shadow_deco1.tr.1", "wall_shadow_deco1.tr.2",
                          "wall_shadow_deco1.tr.3", "wall_shadow_deco1.tr.4",
                          "wall_shadow_deco1.tr.5", "wall_shadow_deco1.tr.6", ],
            br2_tiles=[   "wall_shadow_deco1.br.1", "wall_shadow_deco1.br.2",
                          "wall_shadow_deco1.br.3", "wall_shadow_deco1.br.4",
                          "wall_shadow_deco1.br.5", "wall_shadow_deco1.br.6", ],
            bl2_tiles=[   "wall_shadow_deco1.bl.1", "wall_shadow_deco1.bl.2",
                          "wall_shadow_deco1.bl.3", "wall_shadow_deco1.bl.4",
                          "wall_shadow_deco1.bl.5", "wall_shadow_deco1.bl.6", ],
            )

    tp_init(name="wall_dungeon.3",
            tiles=[       "wall_dungeon.3.1", "wall_dungeon.3.2", "wall_dungeon.3.3", "wall_dungeon.3.4",
                          "wall_dungeon.3.5", "wall_dungeon.3.6", "wall_dungeon.3.7", "wall_dungeon.3.8",
                          "wall_dungeon.3.9", "wall_dungeon.3.10", "wall_dungeon.3.11", "wall_dungeon.3.12",
                          "wall_dungeon.3.13", "wall_dungeon.3.14", "wall_dungeon.3.15", "wall_dungeon.3.16",
                          "wall_dungeon.3.17", "wall_dungeon.3.18", "wall_dungeon.3.19", ],
            left1_tiles=[ "wall_deco1.left.1", "wall_deco1.left.2",
                          "wall_deco1.left.3", "wall_deco1.left.4",
                          "wall_deco1.left.5", "wall_deco1.left.6", ],
            right1_tiles=["wall_deco1.right.1", "wall_deco1.right.2",
                          "wall_deco1.right.3", "wall_deco1.right.4",
                          "wall_deco1.right.5", "wall_deco1.right.6", ],
            top1_tiles=[  "wall_deco1.top.1", "wall_deco1.top.2",
                          "wall_deco1.top.3", "wall_deco1.top.4",
                          "wall_deco1.top.5", "wall_deco1.top.6",
                          "wall_deco1.top.7", ],
            bot1_tiles=[  "wall_deco1.bot.1", "wall_deco1.bot.2",
                          "wall_deco1.bot.3", "wall_deco1.bot.4",
                          "wall_deco1.bot.5", "wall_deco1.bot.6",
                          "wall_deco1.bot.7", ],
            tl1_tiles=[   "wall_deco1.tl.1", "wall_deco1.tl.2",
                          "wall_deco1.tl.3", "wall_deco1.tl.4",
                          "wall_deco1.tl.5", "wall_deco1.tl.6", ],
            tr1_tiles=[   "wall_deco1.tr.1", "wall_deco1.tr.2",
                          "wall_deco1.tr.3", "wall_deco1.tr.4",
                          "wall_deco1.tr.5", "wall_deco1.tr.6", ],
            br1_tiles=[   "wall_deco1.br.1", "wall_deco1.br.2",
                          "wall_deco1.br.3", "wall_deco1.br.4",
                          "wall_deco1.br.5", "wall_deco1.br.6", ],
            bl1_tiles=[   "wall_deco1.bl.1", "wall_deco1.bl.2",
                          "wall_deco1.bl.3", "wall_deco1.bl.4",
                          "wall_deco1.bl.5", "wall_deco1.bl.6", ],
            left2_tiles=[ "wall_shadow_deco1.left.1", "wall_shadow_deco1.left.2",
                          "wall_shadow_deco1.left.3", "wall_shadow_deco1.left.4",
                          "wall_shadow_deco1.left.5", "wall_shadow_deco1.left.6", ],
            right2_tiles=["wall_shadow_deco1.right.1", "wall_shadow_deco1.right.2",
                          "wall_shadow_deco1.right.3", "wall_shadow_deco1.right.4",
                          "wall_shadow_deco1.right.5", "wall_shadow_deco1.right.6", ],
            top2_tiles=[  "wall_shadow_deco1.top.1", "wall_shadow_deco1.top.2",
                          "wall_shadow_deco1.top.3", "wall_shadow_deco1.top.4",
                          "wall_shadow_deco1.top.5", "wall_shadow_deco1.top.6",
                          "wall_shadow_deco1.top.7", ],
            bot2_tiles=[  "wall_shadow_deco1.bot.1", "wall_shadow_deco1.bot.2",
                          "wall_shadow_deco1.bot.3", "wall_shadow_deco1.bot.4",
                          "wall_shadow_deco1.bot.5", "wall_shadow_deco1.bot.6",
                          "wall_shadow_deco1.bot.7", ],
            tl2_tiles=[   "wall_shadow_deco1.tl.1", "wall_shadow_deco1.tl.2",
                          "wall_shadow_deco1.tl.3", "wall_shadow_deco1.tl.4",
                          "wall_shadow_deco1.tl.5", "wall_shadow_deco1.tl.6", ],
            tr2_tiles=[   "wall_shadow_deco1.tr.1", "wall_shadow_deco1.tr.2",
                          "wall_shadow_deco1.tr.3", "wall_shadow_deco1.tr.4",
                          "wall_shadow_deco1.tr.5", "wall_shadow_deco1.tr.6", ],
            br2_tiles=[   "wall_shadow_deco1.br.1", "wall_shadow_deco1.br.2",
                          "wall_shadow_deco1.br.3", "wall_shadow_deco1.br.4",
                          "wall_shadow_deco1.br.5", "wall_shadow_deco1.br.6", ],
            bl2_tiles=[   "wall_shadow_deco1.bl.1", "wall_shadow_deco1.bl.2",
                          "wall_shadow_deco1.bl.3", "wall_shadow_deco1.bl.4",
                          "wall_shadow_deco1.bl.5", "wall_shadow_deco1.bl.6", ],
            )

    tp_init(name="wall_dungeon.4",
            tiles=[       "wall_dungeon.4.1", "wall_dungeon.4.2", "wall_dungeon.4.3", "wall_dungeon.4.4",
                          "wall_dungeon.4.5", "wall_dungeon.4.6", "wall_dungeon.4.7", "wall_dungeon.4.8",
                          "wall_dungeon.4.9", "wall_dungeon.4.10", "wall_dungeon.4.11", "wall_dungeon.4.12",
                          "wall_dungeon.4.13", "wall_dungeon.4.14", "wall_dungeon.4.15", "wall_dungeon.4.16",
                          "wall_dungeon.4.17", "wall_dungeon.4.18", "wall_dungeon.4.19", ],
            left1_tiles=[ "wall_deco1.left.1", "wall_deco1.left.2",
                          "wall_deco1.left.3", "wall_deco1.left.4",
                          "wall_deco1.left.5", "wall_deco1.left.6", ],
            right1_tiles=["wall_deco1.right.1", "wall_deco1.right.2",
                          "wall_deco1.right.3", "wall_deco1.right.4",
                          "wall_deco1.right.5", "wall_deco1.right.6", ],
            top1_tiles=[  "wall_deco1.top.1", "wall_deco1.top.2",
                          "wall_deco1.top.3", "wall_deco1.top.4",
                          "wall_deco1.top.5", "wall_deco1.top.6",
                          "wall_deco1.top.7", ],
            bot1_tiles=[  "wall_deco1.bot.1", "wall_deco1.bot.2",
                          "wall_deco1.bot.3", "wall_deco1.bot.4",
                          "wall_deco1.bot.5", "wall_deco1.bot.6",
                          "wall_deco1.bot.7", ],
            tl1_tiles=[   "wall_deco1.tl.1", "wall_deco1.tl.2",
                          "wall_deco1.tl.3", "wall_deco1.tl.4",
                          "wall_deco1.tl.5", "wall_deco1.tl.6", ],
            tr1_tiles=[   "wall_deco1.tr.1", "wall_deco1.tr.2",
                          "wall_deco1.tr.3", "wall_deco1.tr.4",
                          "wall_deco1.tr.5", "wall_deco1.tr.6", ],
            br1_tiles=[   "wall_deco1.br.1", "wall_deco1.br.2",
                          "wall_deco1.br.3", "wall_deco1.br.4",
                          "wall_deco1.br.5", "wall_deco1.br.6", ],
            bl1_tiles=[   "wall_deco1.bl.1", "wall_deco1.bl.2",
                          "wall_deco1.bl.3", "wall_deco1.bl.4",
                          "wall_deco1.bl.5", "wall_deco1.bl.6", ],
            left2_tiles=[ "wall_shadow_deco1.left.1", "wall_shadow_deco1.left.2",
                          "wall_shadow_deco1.left.3", "wall_shadow_deco1.left.4",
                          "wall_shadow_deco1.left.5", "wall_shadow_deco1.left.6", ],
            right2_tiles=["wall_shadow_deco1.right.1", "wall_shadow_deco1.right.2",
                          "wall_shadow_deco1.right.3", "wall_shadow_deco1.right.4",
                          "wall_shadow_deco1.right.5", "wall_shadow_deco1.right.6", ],
            top2_tiles=[  "wall_shadow_deco1.top.1", "wall_shadow_deco1.top.2",
                          "wall_shadow_deco1.top.3", "wall_shadow_deco1.top.4",
                          "wall_shadow_deco1.top.5", "wall_shadow_deco1.top.6",
                          "wall_shadow_deco1.top.7", ],
            bot2_tiles=[  "wall_shadow_deco1.bot.1", "wall_shadow_deco1.bot.2",
                          "wall_shadow_deco1.bot.3", "wall_shadow_deco1.bot.4",
                          "wall_shadow_deco1.bot.5", "wall_shadow_deco1.bot.6",
                          "wall_shadow_deco1.bot.7", ],
            tl2_tiles=[   "wall_shadow_deco1.tl.1", "wall_shadow_deco1.tl.2",
                          "wall_shadow_deco1.tl.3", "wall_shadow_deco1.tl.4",
                          "wall_shadow_deco1.tl.5", "wall_shadow_deco1.tl.6", ],
            tr2_tiles=[   "wall_shadow_deco1.tr.1", "wall_shadow_deco1.tr.2",
                          "wall_shadow_deco1.tr.3", "wall_shadow_deco1.tr.4",
                          "wall_shadow_deco1.tr.5", "wall_shadow_deco1.tr.6", ],
            br2_tiles=[   "wall_shadow_deco1.br.1", "wall_shadow_deco1.br.2",
                          "wall_shadow_deco1.br.3", "wall_shadow_deco1.br.4",
                          "wall_shadow_deco1.br.5", "wall_shadow_deco1.br.6", ],
            bl2_tiles=[   "wall_shadow_deco1.bl.1", "wall_shadow_deco1.bl.2",
                          "wall_shadow_deco1.bl.3", "wall_shadow_deco1.bl.4",
                          "wall_shadow_deco1.bl.5", "wall_shadow_deco1.bl.6", ],
            )

    tp_init(name="wall_dungeon.5",
            tiles=[       "wall_dungeon.5.1", "wall_dungeon.5.2", "wall_dungeon.5.3", "wall_dungeon.5.4",
                          "wall_dungeon.5.5", "wall_dungeon.5.6", "wall_dungeon.5.7", "wall_dungeon.5.8",
                          "wall_dungeon.5.9", "wall_dungeon.5.10", "wall_dungeon.5.11", "wall_dungeon.5.12",
                          "wall_dungeon.5.13", "wall_dungeon.5.14", "wall_dungeon.5.15", "wall_dungeon.5.16",
                          "wall_dungeon.5.17", "wall_dungeon.5.18", "wall_dungeon.5.19", ],
            left1_tiles=[ "wall_deco1.left.1", "wall_deco1.left.2",
                          "wall_deco1.left.3", "wall_deco1.left.4",
                          "wall_deco1.left.5", "wall_deco1.left.6", ],
            right1_tiles=["wall_deco1.right.1", "wall_deco1.right.2",
                          "wall_deco1.right.3", "wall_deco1.right.4",
                          "wall_deco1.right.5", "wall_deco1.right.6", ],
            top1_tiles=[  "wall_deco1.top.1", "wall_deco1.top.2",
                          "wall_deco1.top.3", "wall_deco1.top.4",
                          "wall_deco1.top.5", "wall_deco1.top.6",
                          "wall_deco1.top.7", ],
            bot1_tiles=[  "wall_deco1.bot.1", "wall_deco1.bot.2",
                          "wall_deco1.bot.3", "wall_deco1.bot.4",
                          "wall_deco1.bot.5", "wall_deco1.bot.6",
                          "wall_deco1.bot.7", ],
            tl1_tiles=[   "wall_deco1.tl.1", "wall_deco1.tl.2",
                          "wall_deco1.tl.3", "wall_deco1.tl.4",
                          "wall_deco1.tl.5", "wall_deco1.tl.6", ],
            tr1_tiles=[   "wall_deco1.tr.1", "wall_deco1.tr.2",
                          "wall_deco1.tr.3", "wall_deco1.tr.4",
                          "wall_deco1.tr.5", "wall_deco1.tr.6", ],
            br1_tiles=[   "wall_deco1.br.1", "wall_deco1.br.2",
                          "wall_deco1.br.3", "wall_deco1.br.4",
                          "wall_deco1.br.5", "wall_deco1.br.6", ],
            bl1_tiles=[   "wall_deco1.bl.1", "wall_deco1.bl.2",
                          "wall_deco1.bl.3", "wall_deco1.bl.4",
                          "wall_deco1.bl.5", "wall_deco1.bl.6", ],
            left2_tiles=[ "wall_shadow_deco1.left.1", "wall_shadow_deco1.left.2",
                          "wall_shadow_deco1.left.3", "wall_shadow_deco1.left.4",
                          "wall_shadow_deco1.left.5", "wall_shadow_deco1.left.6", ],
            right2_tiles=["wall_shadow_deco1.right.1", "wall_shadow_deco1.right.2",
                          "wall_shadow_deco1.right.3", "wall_shadow_deco1.right.4",
                          "wall_shadow_deco1.right.5", "wall_shadow_deco1.right.6", ],
            top2_tiles=[  "wall_shadow_deco1.top.1", "wall_shadow_deco1.top.2",
                          "wall_shadow_deco1.top.3", "wall_shadow_deco1.top.4",
                          "wall_shadow_deco1.top.5", "wall_shadow_deco1.top.6",
                          "wall_shadow_deco1.top.7", ],
            bot2_tiles=[  "wall_shadow_deco1.bot.1", "wall_shadow_deco1.bot.2",
                          "wall_shadow_deco1.bot.3", "wall_shadow_deco1.bot.4",
                          "wall_shadow_deco1.bot.5", "wall_shadow_deco1.bot.6",
                          "wall_shadow_deco1.bot.7", ],
            tl2_tiles=[   "wall_shadow_deco1.tl.1", "wall_shadow_deco1.tl.2",
                          "wall_shadow_deco1.tl.3", "wall_shadow_deco1.tl.4",
                          "wall_shadow_deco1.tl.5", "wall_shadow_deco1.tl.6", ],
            tr2_tiles=[   "wall_shadow_deco1.tr.1", "wall_shadow_deco1.tr.2",
                          "wall_shadow_deco1.tr.3", "wall_shadow_deco1.tr.4",
                          "wall_shadow_deco1.tr.5", "wall_shadow_deco1.tr.6", ],
            br2_tiles=[   "wall_shadow_deco1.br.1", "wall_shadow_deco1.br.2",
                          "wall_shadow_deco1.br.3", "wall_shadow_deco1.br.4",
                          "wall_shadow_deco1.br.5", "wall_shadow_deco1.br.6", ],
            bl2_tiles=[   "wall_shadow_deco1.bl.1", "wall_shadow_deco1.bl.2",
                          "wall_shadow_deco1.bl.3", "wall_shadow_deco1.bl.4",
                          "wall_shadow_deco1.bl.5", "wall_shadow_deco1.bl.6", ],
            )

init()
