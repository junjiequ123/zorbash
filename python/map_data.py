import zx

#
# entrance rooms
#
zx.map_load_room(entrance=True, room_data=[
"      ^      ","             ","             ","             ","             ",
"   ......... ","             ","             ","             ","      ^      ",
"  .CCCCCCC.. ","      ^      ","             ","      ^      ","  CCC....wwk ",
" ..CCCCCCC.. ","    .....    ","    .....    ","    m....    ","  CC......ww ",
" .CCCCCCCC.. ","    .LLL.    ","    .L.L.    ","    .L.L.    "," .CC......ww ",
"<.C..CC.....>","   <..S..>   ","   <..S..>   ","   <..S..    "," .....S..B.m ",
" .Ck..C..... ","    .L...    ","    .LmL.    ","    .L...    "," .m......... ",
" .C..CC.S... ","    ...m.    ","    .....    ","    ....m    "," ......B...| ",
"..CCC.C....m ","             ","             ","             "," ww......m.. ",
"...CCC...... ","             ","             ","             "," www........ ",
"...........  ","             ","             ","             "," wwww.m.www. ",
"..........   ","             ","             ","             "," wwww..wwww  ",
"  ....v...   ","             ","             ","             ","             ",
])

#
# exit rooms
#
zx.map_load_room(exit=True, room_data=[
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"      ^      ","      ^      ","             ","      ^      ","      ^      ",
"    ww...    ","    .....    ","    .....    ","    .....    ","    .....    ",
"    ww...    ","    .L...    ","    .L...    ","    .L...    ","    .L...    ",
"   <..E..>   ","   <..E..>   ","   <..E..>   ","   <..E..    ","    ..E..    ",
"    .www.    ","    .L...    ","    .L...    ","    .L...    ","    .L...    ",
"    ...ww    ","    .....    ","    .....    ","    .....    ","    .....    ",
"      v      ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# directional combined with exit rooms
#
zx.map_load_room(left=True, room_data=[
"             ","             ","             ","             ","             ",
"      ^      ","      ^      ","             ","      ^      ","      ^      ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ....L....  ","  ....L....  ","  ....L....  ","  ....L....  ","  ....L....  ",
"  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ",
" <..LLLLL..> "," <..LLLLL..> "," <..LLLLL..> "," <..LLLLL..  ","  ..LLLLL..  ",
"  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ",
"  ....L....  ","  ....L....  ","  ....L....  ","  ....L....  ","  ....L....  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"      v      ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# lock rooms
#
zx.map_load_room(lock=True, room_data=[
"    ^X  X    ","             ","             ","             ","             ",
"  X .....    ","      ^      ","             ","      ^      ","      ^      ",
"  ....|....X ","  .........  ","  .........  ","  .........  ","  .........  ",
"<...|.L.|..  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...LLL.... ","  ...L.....  ","  ...L.....  ","  ...L.....  ","  ...L.....  ",
"  .|LLfLL|..>"," <...L.....> "," <...L.....> "," <...L.....  ","  ...L.....  ",
" X...LLL.... ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  ..|.L.|..X ","  .........  ","  .........  ","  .........  ","  .........  ",
"   ...|...   ","  .........  ","  .........  ","  .........  ","  .........  ",
"   X ... X   ","             ","             ","             ","             ",
"      v      ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# key rooms
#
zx.map_load_room(key=True, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  ........k  ",
"  .........  ","  .........  ","  ...k.....  ","  .......k.  ","  .........  ",
"  .....k...  ","  .........  ","  .........  ","  .........  ","  .........  ",
" <.........  "," <.........  "," <.........  "," <.........  ","  .........  ",
"  .........> ","  ....k....> ","  .........> ","  .........  ","  .........  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# depth 1 rooms
#
zx.map_load_room(depth=1, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  ww.......  ","  .........  ","  .........  ","  .........  ",
"  ...ww....  ","  www......  ","  ...LL....  ","  ...LL....  ","  ...LL....  ",
"  ....w....  ","  .w.w.....  ","  ....L....  ","  ....L....  ","  ....L....  ",
" <....w....  "," <...www...  "," <....L....  "," <....L....  ","  ....L....  ",
"  ....w....> ","  ....www..> ","  ....L....> ","  ....L....  ","  ....L....  ",
"  ...www...  ","  .........  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# depth 2 rooms
#
zx.map_load_room(depth=2, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ",
"  .....L...  ","  .....L...  ","  .....L...  ","  .....L...  ","  .....L...  ",
" <...LLL...  "," <...LLL...  "," <...LLL...  "," <...LLL...  ","  ...LLL...  ",
"  ...L.....> ","  ...L.....> ","  ...L.....> ","  ...L.....  ","  ...L.....  ",
"  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# depth 3 rooms
#
zx.map_load_room(depth=3, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  .....L...  ","  .....L...  ","  .....L...  ","  .....L...  ","  .....L...  ",
" <...LLL...  "," <...LLL...  "," <...LLL...  "," <...LLL...  ","  ...LLL...  ",
"  .....L...> ","  .....L...> ","  .....L...> ","  .....L...  ","  .....L...  ",
"  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# depth 4 rooms
#
zx.map_load_room(depth=4, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...L.L...  ","  ...L.L...  ","  ...L.L...  ","  ...L.L...  ","  ...L.L...  ",
"  ...L.L...  ","  ...L.L...  ","  ...L.L...  ","  ...L.L...  ","  ...L.L...  ",
" <...LLL...  "," <...LLL...  "," <...LLL...  "," <...LLL...  ","  ...LLL...  ",
"  .....L...> ","  .....L...> ","  .....L...> ","  .....L...  ","  .....L...  ",
"  .....L...  ","  .....L...  ","  .....L...  ","  .....L...  ","  .....L...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# depth 5 rooms
#
zx.map_load_room(depth=5, room_data=[
"             ","             ","             ","             ","             ",
"   ^         ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  ...L.....  ","  ...L.....  ","  ...L.....  ","  ...L.....  ","  ...L.....  ",
" <...LfL...  "," <...LfL.f.  "," <...LfL...  "," <.f.LLL...  ","  .f.LfL...  ",
"  .....L...> ","  .....L...> ","  .....L...> ","  .....L...  ","  .....L...  ",
"  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"         v   ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# depth 6 rooms
#
zx.map_load_room(depth=6, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...www...  ","  ...www...  ","  ...www...  ","  ...www...  ","  ...www...  ",
"  ...w.....  ","  ...w.....  ","  ...w.....  ","  ...w.....  ","  ...w.....  ",
" <...www...  "," <...www...  "," <...www...  "," <...www...  ","  ...www...  ",
"  ...wWw...> ","  ...wWw...> ","  ...wWw...> ","  ...wWw...  ","  ...wWw...  ",
"  ...www...  ","  ...www...  ","  ...www...  ","  ...www...  ","  ...www...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# secret rooms
#
zx.map_load_room(secret=True, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ","  ...LL....  ",
"  ..L..L...  ","  ..L..L...  ","  ..L..L...  ","  ..L..L...  ","  ..L..L...  ",
" <....L....  "," <....L....  "," <....L....  "," <....L....  ","  ....L....  ",
"  ....L....> ","  ....L....> ","  ....L....> ","  ....L....  ","  ....L....  ",
"  ....L....  ","  ....L....  ","  ....L....  ","  ....L....  ","  ....L....  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

