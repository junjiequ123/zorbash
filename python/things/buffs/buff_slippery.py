import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel slippery as a banana.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You return to your normal level of stickiness.")


def tp_init(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.is_slippery(self, True)
    my.long_text_description(self, "No more trapped in webs for you! With this buff you can glide with ease through the cobwebs.")
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.text_description(self, "You are as slippery as a banana buff.")
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile="buff_slippery")
    # my.z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(self)


def init():
    tp_init(name="buff_slippery", text_name="slippery as the banana")


init()
