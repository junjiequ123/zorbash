import zx
import tp


def tp_init(name, tiles=[], left1_tiles=[]):
    x = tp.Tp(name)

    x.set_is_cursor_can_hover_over(True)
    x.set_is_dirt(True)
    x.set_is_interesting(False)
    x.set_is_loggable(False)
    x.set_text_a_or_an("the");
    x.set_z_depth(zx.MAP_DEPTH_FLOOR)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="dirt1",
            tiles=[
                        "dirt1.1", "dirt1.2", "dirt1.3", "dirt1.4",
                        "dirt1.5", "dirt1.6", "dirt1.7", "dirt1.8",
                        "dirt1.9", "dirt1.10", "dirt1.11", "dirt1.12",
                        "dirt1.13", "dirt1.14", "dirt1.15", "dirt1.16",
                        "dirt1.17", "dirt1.18", "dirt1.19",
                ])
    tp_init(name="dirt2",
            tiles=[
                        "dirt2.1", "dirt2.2", "dirt2.3", "dirt2.4",
                        "dirt2.5", "dirt2.6", "dirt2.7", "dirt2.8",
                        "dirt2.9", "dirt2.10", "dirt2.11", "dirt2.12",
                        "dirt2.13", "dirt2.14", "dirt2.15", "dirt2.16",
                        "dirt2.17", "dirt2.18", "dirt2.19",
                ])
    tp_init(name="dirt3",
            tiles=[
                        "dirt3.1", "dirt3.2", "dirt3.3", "dirt3.4",
                        "dirt3.5", "dirt3.6", "dirt3.7", "dirt3.8",
                        "dirt3.9", "dirt3.10", "dirt3.11", "dirt3.12",
                        "dirt3.13", "dirt3.14", "dirt3.15", "dirt3.16",
                        "dirt3.17", "dirt3.18", "dirt3.19",
                ])
init()
