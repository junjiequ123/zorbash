import zx

#
# entrance rooms
#
zx.map_load_room(entrance=True, room_data=[
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"      ^      ","      ^      ","             ","      ^      ","      ^      ",
"    .....    ","    .....    ","    .....    ","    .....    ","    .....    ",
"    .L...    ","    .L...    ","    .L.L.    ","    .L.L.    ","    .LLL.    ",
"   <..S..>   ","   <..S..>   ","   <..S..>   ","   <..S..    ","    .LS..    ",
"    .L...    ","    .L...    ","    .L.L.    ","    .L...    ","    .L.L.    ",
"    .....    ","    .....    ","    .....    ","    .....    ","    .....    ",
"      v      ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# exit rooms
#
zx.map_load_room(exit=True, room_data=[
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"      ^      ","      ^      ","             ","      ^      ","      ^      ",
"    .....    ","    .....    ","    .....    ","    .....    ","    .....    ",
"    .?...    ","    .?...    ","    .?...    ","    .?...    ","    .?...    ",
"   <..E..>   ","   <..E..>   ","   <..E..>   ","   <..E..    ","    ..E..    ",
"    .?...    ","    .?...    ","    .?...    ","    .?...    ","    .?...    ",
"    .....    ","    .....    ","    .....    ","    .....    ","    .....    ",
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
"  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ",
"  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ",
" <..?????..> "," <..?????..> "," <..?????..> "," <..?????..  ","  ..?????..  ",
"  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ",
"  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ",
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
"             ","             ","             ","             ","             ",
"      ^      ","      ^      ","             ","      ^      ","      ^      ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...L.....  ","  ...L.....  ","  ...L.....  ","  ...L.....  ","  ...L.....  ",
" <...L.....> "," <...L.....> "," <...L.....> "," <...L.....  ","  ...L.....  ",
"  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ","  ...LLL...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"      v      ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

#
# key rooms
#
zx.map_load_room(key=True, room_data=[
"             ","             ","             ","             ","             ",
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
" <....k....  "," <....k....  "," <....k....  "," <....k....  ","  ....k....  ",
"  .........> ","  .........> ","  .........> ","  .........  ","  .........  ",
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
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ",
"  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ",
" <....?....  "," <....?....  "," <....?....  "," <....?....  ","  ....?....  ",
"  ....?....> ","  ....?....> ","  ....?....> ","  ....?....  ","  ....?....  ",
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
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
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
"  .....?...  ","  .....?...  ","  .....?...  ","  .....?...  ","  .....?...  ",
" <...???...  "," <...???...  "," <...???...  "," <...???...  ","  ...???...  ",
"  ...?.....> ","  ...?.....> ","  ...?.....> ","  ...?.....  ","  ...?.....  ",
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
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
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
"  .....?...  ","  .....?...  ","  .....?...  ","  .....?...  ","  .....?...  ",
" <...???...  "," <...???...  "," <...???...  "," <...???...  ","  ...???...  ",
"  .....?...> ","  .....?...> ","  .....?...> ","  .....?...  ","  .....?...  ",
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
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
"  ...?.?...  ","  ...?.?...  ","  ...?.?...  ","  ...?.?...  ","  ...?.?...  ",
"  ...?.?...  ","  ...?.?...  ","  ...?.?...  ","  ...?.?...  ","  ...?.?...  ",
" <...???...  "," <...???...  "," <...???...  "," <...???...  ","  ...???...  ",
"  .....?...> ","  .....?...> ","  .....?...> ","  .....?...  ","  .....?...  ",
"  .....?...  ","  .....?...  ","  .....?...  ","  .....?...  ","  .....?...  ",
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
"    ^        ","    ^        ","             ","    ^        ","    ^        ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
"  ...?.....  ","  ...?.....  ","  ...?.....  ","  ...?.....  ","  ...?.....  ",
" <...???...  "," <...???...  "," <...???...  "," <...???...  ","  ...???...  ",
"  .....?...> ","  .....?...> ","  .....?...> ","  .....?...  ","  .....?...  ",
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
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
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
"  ...?.....  ","  ...?.....  ","  ...?.....  ","  ...?.....  ","  ...?.....  ",
" <...???...  "," <...???...  "," <...???...  "," <...???...  ","  ...???...  ",
"  ...?.?...> ","  ...?.?...> ","  ...?.?...> ","  ...?.?...  ","  ...?.?...  ",
"  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ","  ...???...  ",
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
"  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ","  ...??....  ",
"  ..?..?...  ","  ..?..?...  ","  ..?..?...  ","  ..?..?...  ","  ..?..?...  ",
" <....?....  "," <....?....  "," <....?....  "," <....?....  ","  ....?....  ",
"  ....?....> ","  ....?....> ","  ....?....> ","  ....?....  ","  ....?....  ",
"  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ","  ....?....  ",
"  .........  ","  .........  ","  .........  ","  .........  ","  .........  ",
"        v    ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
"             ","             ","             ","             ","             ",
])

