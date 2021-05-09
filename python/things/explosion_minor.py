import zx
import tp

def on_death(me, x, y):
    zx.thing_sound_play_channel(me, zx.CHANNEL_EXPLOSION, "explosion_a")

def tp_init(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_small_shadow_caster(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_floating(True)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_on_death_do("explosion_minor.on_death()")
    mytp.set_z_depth(zx.MAP_DEPTH_EXPLOSION_MINOR)
    mytp.set_z_prio(zx.MAP_PRIO_INFRONT)

    mytp.set_tile(tile="nothing")
    mytp.set_tile("explosion_minor.1", delay_ms=50)
    mytp.set_tile("explosion_minor.2", delay_ms=50)
    mytp.set_tile("explosion_minor.3", delay_ms=50)
    mytp.set_tile("explosion_minor.4", delay_ms=50, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="explosion_minor")

init()