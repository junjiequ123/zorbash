import zx
import tp


def water_init(name, short_name, 
              tiles=[],
              left_tiles=[]):
    
    x = tp.Tp(name)

    x.set_is_boring(True)
    x.set_is_water(True)
    x.set_is_animated(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_WATER)
    
    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

def init():
    water_init(name="water1", short_name="water", 
            tiles=[ 
                "water1.1", 
                "water1.2", 
                "water1.3", 
                "water1.4", 
                "water1.5", 
                "water1.6", 
                "water1.7", 
                "water1.8", 
                ])
init()
