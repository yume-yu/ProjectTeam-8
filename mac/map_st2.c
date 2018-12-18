#include "theBeautifulSky.h"
/* ステージ2のマップと座標 */

char *(map_st2)[WIDTH - 2] = {
	"                          ┏┓            ^       ^       ",
	"             ^        ^   ┗┫    ^           ^           ",
  "   ^     ^    ^   ^        ▲        ^                    ",
	"                          ▲ ▲           ^        ^       ",
	"     ^      ^     ^   _Π | ■ |Π _                         ",
	"                     | ■ |   | ■ |   ^   ^     ^     ^    ",
	" ^   ^   ^     ^     |   | ∩ |   |     ^     ^            ",
	"                                                 ^    ^   ",
	"   ^  ^    ^   ^         │  │  ^         ^              ",
	"          __Π _    ^   ^ │  │      __Π _        ^       ",
	" ^       /____/＼        │  │^    /____/＼   ^          ",
  "    ^    |田 |  |   ^    │  │     |田 |  |      ^       ",
	"         |   |∩ |        │  │ ^   |   |∩ |              ",
	"    ^                 ^  │  │                       ^   ",
	" ^   ^      │  │         │  │         │  │          ",
	"          ^ │  └─────────┘  └─────────┘  │     ^",
	"  ^   ^     │                            │      ^     ",
	"      ^     └────────────┐  ┌────────────┘ ",
	"          ^          ^   │  │                  ^        ",
	"   ^  ^        ^         │  │   ^                       ",
	"                  ^      │  │        ^    ^         ^  ",
	" ^    ^     ^         ^  │  │      ^    ^               ",
	"                  ^      │  │                 ^         ",
};

arrow_pos st2_pos[WIDTH - 2][HEIGHT - 2] ={
	{{ 2, 2,0,0},{ 2, 3,0,0},{ 2, 4,0,0},{ 2, 5,0,0},{ 2, 6,0,0},{ 2, 7,0,0},{ 2, 8,0,0},{ 2, 9,0,0},{ 2,10,0,0},{ 2,11,0,0},{ 2,12,0,0},{ 2,13,0,0},{ 2,14,0,0},{ 2,15,0,0},{ 2,16,0,0},{ 2,17,0,0},{ 2,18,0,0},{ 2,19,0,0},{ 2,20,0,0},{ 2,21,0,0},{ 2,22,0,0},{ 2,23,0,0},{ 2,24,0,0}},
	{{ 3, 2,0,0},{ 3, 3,0,0},{ 3, 4,0,0},{ 3, 5,0,0},{ 3, 6,0,0},{ 3, 7,0,0},{ 3, 8,0,0},{ 3, 9,0,0},{ 3,10,0,0},{ 3,11,0,0},{ 3,12,0,0},{ 3,13,0,0},{ 3,14,0,0},{ 3,15,0,0},{ 3,16,0,0},{ 3,17,0,0},{ 3,18,0,0},{ 3,19,0,0},{ 3,20,0,0},{ 3,21,0,0},{ 3,22,0,0},{ 3,23,0,0},{ 3,24,0,0}},
	{{ 4, 2,0,0},{ 4, 3,0,0},{ 4, 4,0,0},{ 4, 5,0,0},{ 4, 6,0,0},{ 4, 7,0,0},{ 4, 8,0,0},{ 4, 9,0,0},{ 4,10,0,0},{ 4,11,0,0},{ 4,12,0,0},{ 4,13,0,0},{ 4,14,0,0},{ 4,15,0,0},{ 4,16,0,0},{ 4,17,0,0},{ 4,18,0,0},{ 4,19,0,0},{ 4,20,0,0},{ 4,21,0,0},{ 4,22,0,0},{ 4,23,0,0},{ 4,24,0,0}},
	{{ 5, 2,0,0},{ 5, 3,0,0},{ 5, 4,0,0},{ 5, 5,0,0},{ 5, 6,0,0},{ 5, 7,0,0},{ 5, 8,0,0},{ 5, 9,0,0},{ 5,10,0,0},{ 5,11,0,0},{ 5,12,0,0},{ 5,13,0,0},{ 5,14,0,0},{ 5,15,0,0},{ 5,16,0,0},{ 5,17,0,0},{ 5,18,0,0},{ 5,19,0,0},{ 5,20,0,0},{ 5,21,0,0},{ 5,22,0,0},{ 5,23,0,0},{ 5,24,0,0}},
	{{ 6, 2,0,0},{ 6, 3,0,0},{ 6, 4,0,0},{ 6, 5,0,0},{ 6, 6,0,0},{ 6, 7,0,0},{ 6, 8,0,0},{ 6, 9,0,0},{ 6,10,0,0},{ 6,11,0,0},{ 6,12,0,0},{ 6,13,0,0},{ 6,14,0,0},{ 6,15,0,0},{ 6,16,0,0},{ 6,17,0,0},{ 6,18,0,0},{ 6,19,0,0},{ 6,20,0,0},{ 6,21,0,0},{ 6,22,0,0},{ 6,23,0,0},{ 6,24,0,0}},
	{{ 7, 2,0,0},{ 7, 3,0,0},{ 7, 4,0,0},{ 7, 5,0,0},{ 7, 6,0,0},{ 7, 7,0,0},{ 7, 8,0,0},{ 7, 9,0,0},{ 7,10,0,0},{ 7,11,0,0},{ 7,12,0,0},{ 7,13,0,0},{ 7,14,0,0},{ 7,15,0,0},{ 7,16,0,0},{ 7,17,0,0},{ 7,18,0,0},{ 7,19,0,0},{ 7,20,0,0},{ 7,21,0,0},{ 7,22,0,0},{ 7,23,0,0},{ 7,24,0,0}},
	{{ 8, 2,0,0},{ 8, 3,0,0},{ 8, 4,0,0},{ 8, 5,0,0},{ 8, 6,0,0},{ 8, 7,0,0},{ 8, 8,0,0},{ 8, 9,0,0},{ 8,10,0,0},{ 8,11,0,0},{ 8,12,0,0},{ 8,13,0,0},{ 8,14,0,0},{ 8,15,0,0},{ 8,16,0,0},{ 8,17,0,0},{ 8,18,0,0},{ 8,19,0,0},{ 8,20,0,0},{ 8,21,0,0},{ 8,22,0,0},{ 8,23,0,0},{ 8,24,0,0}},
	{{ 9, 2,0,0},{ 9, 3,0,0},{ 9, 4,0,0},{ 9, 5,0,0},{ 9, 6,0,0},{ 9, 7,0,0},{ 9, 8,0,0},{ 9, 9,0,0},{ 9,10,0,0},{ 9,11,0,0},{ 9,12,0,0},{ 9,13,0,0},{ 9,14,0,0},{ 9,15,0,0},{ 9,16,0,0},{ 9,17,0,0},{ 9,18,0,0},{ 9,19,0,0},{ 9,20,0,0},{ 9,21,0,0},{ 9,22,0,0},{ 9,23,0,0},{ 9,24,0,0}},
	{{10, 2,0,0},{10, 3,0,0},{10, 4,0,0},{10, 5,0,0},{10, 6,0,0},{10, 7,0,0},{10, 8,0,0},{10, 9,0,0},{10,10,0,0},{10,11,0,0},{10,12,0,0},{10,13,0,0},{10,14,0,0},{10,15,0,0},{10,16,0,0},{10,17,0,0},{10,18,0,0},{10,19,0,0},{10,20,0,0},{10,21,0,0},{10,22,0,0},{10,23,0,0},{10,24,0,0}},
	{{11, 2,0,0},{11, 3,0,0},{11, 4,0,0},{11, 5,0,0},{11, 6,0,0},{11, 7,0,0},{11, 8,0,0},{11, 9,0,0},{11,10,0,0},{11,11,0,0},{11,12,0,0},{11,13,0,0},{11,14,0,0},{11,15,0,0},{11,16,0,0},{11,17,0,0},{11,18,0,0},{11,19,0,0},{11,20,0,0},{11,21,0,0},{11,22,0,0},{11,23,0,0},{11,24,0,0}},
	{{12, 2,0,0},{12, 3,0,0},{12, 4,0,0},{12, 5,0,0},{12, 6,0,0},{12, 7,0,0},{12, 8,0,0},{12, 9,0,0},{12,10,0,0},{12,11,0,0},{12,12,0,0},{12,13,0,0},{12,14,0,0},{12,15,0,0},{12,16,0,0},{12,17,0,0},{12,18,0,0},{12,19,0,0},{12,20,0,0},{12,21,0,0},{12,22,0,0},{12,23,0,0},{12,24,0,0}},
	{{13, 2,0,0},{13, 3,0,0},{13, 4,0,0},{13, 5,0,0},{13, 6,0,0},{13, 7,0,0},{13, 8,0,0},{13, 9,0,0},{13,10,0,0},{13,11,0,0},{13,12,0,0},{13,13,0,0},{13,14,0,0},{13,15,0,0},{13,16,0,0},{13,17,0,0},{13,18,0,0},{13,19,0,0},{13,20,0,0},{13,21,0,0},{13,22,0,0},{13,23,0,0},{13,24,0,0}},
	{{14, 2,0,0},{14, 3,0,0},{14, 4,0,0},{14, 5,0,0},{14, 6,0,0},{14, 7,0,0},{14, 8,0,0},{14, 9,0,0},{14,10,0,0},{14,11,0,0},{14,12,0,0},{14,13,0,0},{14,14,0,0},{14,15,1,0},{14,16,1,0},{14,17,1,0},{14,18,1,0},{14,19,1,0},{14,20,0,0},{14,21,0,0},{14,22,0,0},{14,23,0,0},{14,24,0,0}},
	{{15, 2,0,0},{15, 3,0,0},{15, 4,0,0},{15, 5,0,0},{15, 6,0,0},{15, 7,0,0},{15, 8,0,0},{15, 9,0,0},{15,10,0,0},{15,11,0,0},{15,12,0,0},{15,13,0,0},{15,14,0,0},{15,15,0,1},{15,16,0,0},{15,17,0,0},{15,18,0,0},{15,19,1,0},{15,20,0,0},{15,21,0,0},{15,22,0,0},{15,23,0,0},{15,24,0,0}},
	{{16, 2,0,0},{16, 3,0,0},{16, 4,0,0},{16, 5,0,0},{16, 6,0,0},{16, 7,0,0},{16, 8,0,0},{16, 9,0,0},{16,10,0,0},{16,11,0,0},{16,12,0,0},{16,13,0,0},{16,14,0,0},{16,15,0,1},{16,16,1,0},{16,17,1,0},{16,18,0,0},{16,19,1,0},{16,20,0,0},{16,21,0,0},{16,22,0,0},{16,23,0,0},{16,24,0,0}},
	{{17, 2,0,0},{17, 3,0,0},{17, 4,0,0},{17, 5,0,0},{17, 6,0,0},{17, 7,0,0},{17, 8,0,0},{17, 9,0,0},{17,10,0,0},{17,11,0,0},{17,12,0,0},{17,13,0,0},{17,14,0,0},{17,15,1,0},{17,16,1,0},{17,17,1,0},{17,18,0,0},{17,19,1,0},{17,20,0,0},{17,21,0,0},{17,22,0,0},{17,23,0,0},{17,24,0,0}},
	{{18, 2,0,0},{18, 3,0,0},{18, 4,0,0},{18, 5,0,0},{18, 6,0,0},{18, 7,0,0},{18, 8,0,0},{18, 9,0,0},{18,10,0,0},{18,11,0,0},{18,12,0,0},{18,13,0,0},{18,14,0,0},{18,15,0,0},{18,16,0,0},{18,17,1,0},{18,18,0,0},{18,19,1,0},{18,20,0,0},{18,21,0,0},{18,22,0,0},{18,23,0,0},{18,24,0,0}},
	{{19, 2,0,0},{19, 3,0,0},{19, 4,0,0},{19, 5,0,0},{19, 6,0,0},{19, 7,0,0},{19, 8,0,0},{19, 9,0,0},{19,10,0,0},{19,11,0,0},{19,12,0,0},{19,13,0,0},{19,14,0,0},{19,15,0,0},{19,16,0,0},{19,17,1,0},{19,18,0,0},{19,19,1,0},{19,20,0,0},{19,21,0,0},{19,22,0,0},{19,23,0,0},{19,24,0,0}},
	{{20, 2,0,0},{20, 3,0,0},{20, 4,0,0},{20, 5,0,0},{20, 6,0,0},{20, 7,0,0},{20, 8,0,0},{20, 9,0,0},{20,10,0,0},{20,11,0,0},{20,12,0,0},{20,13,0,0},{20,14,0,0},{20,15,0,0},{20,16,0,0},{20,17,1,0},{20,18,0,0},{20,19,1,0},{20,20,0,0},{20,21,0,0},{20,22,0,0},{20,23,0,0},{20,24,0,0}},
	{{21, 2,0,0},{21, 3,0,0},{21, 4,0,0},{21, 5,0,0},{21, 6,0,0},{21, 7,0,0},{21, 8,0,0},{21, 9,0,0},{21,10,0,0},{21,11,0,0},{21,12,0,0},{21,13,0,0},{21,14,0,0},{21,15,0,0},{21,16,0,0},{21,17,1,0},{21,18,0,0},{21,19,1,0},{21,20,0,0},{21,21,0,0},{21,22,0,0},{21,23,0,0},{21,24,0,0}},
	{{22, 2,0,0},{22, 3,0,0},{22, 4,0,0},{22, 5,0,0},{22, 6,0,0},{22, 7,0,0},{22, 8,0,0},{22, 9,0,0},{22,10,0,0},{22,11,0,0},{22,12,0,0},{22,13,0,0},{22,14,0,0},{22,15,0,0},{22,16,0,0},{22,17,1,0},{22,18,0,0},{22,19,1,0},{22,20,0,0},{22,21,0,0},{22,22,0,0},{22,23,0,0},{22,24,0,0}},
	{{23, 2,0,0},{23, 3,0,0},{23, 4,0,0},{23, 5,0,0},{23, 6,0,0},{23, 7,0,0},{23, 8,0,0},{23, 9,0,0},{23,10,0,0},{23,11,0,0},{23,12,0,0},{23,13,0,0},{23,14,0,0},{23,15,0,0},{23,16,0,0},{23,17,1,0},{23,18,0,0},{23,19,1,0},{23,20,0,0},{23,21,0,0},{23,22,0,0},{23,23,0,0},{23,24,0,0}},
	{{24, 2,0,0},{24, 3,0,0},{24, 4,0,0},{24, 5,0,0},{24, 6,0,0},{24, 7,0,0},{24, 8,0,0},{24, 9,0,0},{24,10,0,0},{24,11,0,0},{24,12,0,0},{24,13,0,0},{24,14,0,0},{24,15,0,0},{24,16,0,0},{24,17,1,0},{24,18,0,0},{24,19,1,0},{24,20,0,0},{24,21,0,0},{24,22,0,0},{24,23,0,0},{24,24,0,0}},
	{{25, 2,0,0},{25, 3,0,0},{25, 4,0,0},{25, 5,0,0},{25, 6,0,0},{25, 7,0,0},{25, 8,0,0},{25, 9,0,0},{25,10,0,0},{25,11,0,0},{25,12,0,0},{25,13,0,0},{25,14,0,0},{25,15,0,0},{25,16,0,0},{25,17,1,0},{25,18,0,0},{25,19,1,0},{25,20,0,0},{25,21,0,0},{25,22,0,0},{25,23,0,0},{25,24,0,0}},
	{{26, 2,0,0},{26, 3,0,0},{26, 4,0,0},{26, 5,0,0},{26, 6,0,0},{26, 7,0,0},{26, 8,0,0},{26, 9,0,0},{26,10,0,0},{26,11,0,0},{26,12,0,0},{26,13,0,0},{26,14,0,0},{26,15,0,0},{26,16,0,0},{26,17,1,0},{26,18,0,0},{26,19,1,0},{26,20,0,0},{26,21,0,0},{26,22,0,0},{26,23,0,0},{26,24,0,0}},
	{{27, 2,0,0},{27, 3,0,0},{27, 4,0,0},{27, 5,0,0},{27, 6,0,0},{27, 7,0,0},{27, 8,1,0},{27, 9,1,0},{27,10,1,0},{27,11,1,0},{27,12,1,0},{27,13,1,0},{27,14,1,0},{27,15,1,0},{27,16,1,0},{27,17,1,0},{27,18,0,0},{27,19,1,0},{27,20,1,0},{27,21,1,0},{27,22,1,0},{27,23,1,0},{27,24,1,0}},
	{{28, 2,0,0},{28, 3,0,0},{28, 4,0,0},{28, 5,0,0},{28, 6,0,0},{28, 7,0,0},{28, 8,0,0},{28, 9,0,1},{28,10,0,0},{28,11,0,0},{28,12,0,0},{28,13,0,0},{28,14,0,0},{28,15,0,0},{28,16,0,0},{28,17,0,0},{28,18,0,0},{28,19,0,0},{28,20,0,0},{28,21,0,0},{28,22,0,0},{28,23,0,0},{28,24,0,0}},
	{{29, 2,0,0},{29, 3,0,0},{29, 4,0,0},{29, 5,0,0},{29, 6,0,0},{29, 7,0,0},{29, 8,0,0},{29, 9,0,1},{29,10,1,0},{29,11,1,0},{29,12,1,0},{29,13,1,0},{29,14,1,0},{29,15,1,0},{29,16,1,0},{29,17,1,0},{29,18,0,0},{29,19,1,0},{29,20,1,0},{29,21,1,0},{29,22,1,0},{29,23,1,0},{29,24,1,0}},
	{{30, 2,0,0},{30, 3,0,0},{30, 4,0,0},{30, 5,0,0},{30, 6,0,0},{30, 7,0,0},{30, 8,1,0},{30, 9,1,0},{30,10,1,0},{30,11,1,0},{30,12,1,0},{30,13,1,0},{30,14,1,0},{30,15,1,0},{30,16,1,0},{30,17,1,0},{30,18,0,0},{30,19,1,0},{30,20,1,0},{30,21,1,0},{30,22,1,0},{30,23,1,0},{30,24,1,0}},
	{{31, 2,0,0},{31, 3,0,0},{31, 4,0,0},{31, 5,0,0},{31, 6,0,0},{31, 7,0,0},{31, 8,0,0},{31, 9,0,0},{31,10,0,0},{31,11,0,0},{31,12,0,0},{31,13,0,0},{31,14,0,0},{31,15,0,0},{31,16,0,0},{31,17,1,0},{31,18,0,0},{31,19,1,0},{31,20,0,0},{31,21,0,0},{31,22,0,0},{31,23,0,0},{31,24,0,0}},
	{{32, 2,0,0},{32, 3,0,0},{32, 4,0,0},{32, 5,0,0},{32, 6,0,0},{32, 7,0,0},{32, 8,0,0},{32, 9,0,0},{32,10,0,0},{32,11,0,0},{32,12,0,0},{32,13,0,0},{32,14,0,0},{32,15,0,0},{32,16,0,0},{32,17,1,0},{32,18,0,0},{32,19,1,0},{32,20,0,0},{32,21,0,0},{32,22,0,0},{32,23,0,0},{32,24,0,0}},
	{{33, 2,0,0},{33, 3,0,0},{33, 4,0,0},{33, 5,0,0},{33, 6,0,0},{33, 7,0,0},{33, 8,0,0},{33, 9,0,0},{33,10,0,0},{33,11,0,0},{33,12,0,0},{33,13,0,0},{33,14,0,0},{33,15,0,0},{33,16,0,0},{33,17,1,0},{33,18,0,0},{33,19,1,0},{33,20,0,0},{33,21,0,0},{33,22,0,0},{33,23,0,0},{33,24,0,0}},
	{{34, 2,0,0},{34, 3,0,0},{34, 4,0,0},{34, 5,0,0},{34, 6,0,0},{34, 7,0,0},{34, 8,0,0},{34, 9,0,0},{34,10,0,0},{34,11,0,0},{34,12,0,0},{34,13,0,0},{34,14,0,0},{34,15,0,0},{34,16,0,0},{34,17,1,0},{34,18,0,0},{34,19,1,0},{34,20,0,0},{34,21,0,0},{34,22,0,0},{34,23,0,0},{34,24,0,0}},
	{{35, 2,0,0},{35, 3,0,0},{35, 4,0,0},{35, 5,0,0},{35, 6,0,0},{35, 7,0,0},{35, 8,0,0},{35, 9,0,0},{35,10,0,0},{35,11,0,0},{35,12,0,0},{35,13,0,0},{35,14,0,0},{35,15,0,0},{35,16,0,0},{35,17,1,0},{35,18,0,0},{35,19,1,0},{35,20,0,0},{35,21,0,0},{35,22,0,0},{35,23,0,0},{35,24,0,0}},
	{{36, 2,0,0},{36, 3,0,0},{36, 4,0,0},{36, 5,0,0},{36, 6,0,0},{36, 7,0,0},{36, 8,0,0},{36, 9,0,0},{36,10,0,0},{36,11,0,0},{36,12,0,0},{36,13,0,0},{36,14,0,0},{36,15,0,0},{36,16,0,0},{36,17,1,0},{36,18,0,0},{36,19,1,0},{36,20,0,0},{36,21,0,0},{36,22,0,0},{36,23,0,0},{36,24,0,0}},
	{{37, 2,0,0},{37, 3,0,0},{37, 4,0,0},{37, 5,0,0},{37, 6,0,0},{37, 7,0,0},{37, 8,0,0},{37, 9,0,0},{37,10,0,0},{37,11,0,0},{37,12,0,0},{37,13,0,0},{37,14,0,0},{37,15,0,0},{37,16,0,0},{37,17,1,0},{37,18,0,0},{37,19,1,0},{37,20,0,0},{37,21,0,0},{37,22,0,0},{37,23,0,0},{37,24,0,0}},
	{{38, 2,0,0},{38, 3,0,0},{38, 4,0,0},{38, 5,0,0},{38, 6,0,0},{38, 7,0,0},{38, 8,0,0},{38, 9,0,0},{38,10,0,0},{38,11,0,0},{38,12,0,0},{38,13,0,0},{38,14,0,0},{38,15,0,0},{38,16,0,0},{38,17,1,0},{38,18,0,0},{38,19,1,0},{38,20,0,0},{38,21,0,0},{38,22,0,0},{38,23,0,0},{38,24,0,0}},
	{{39, 2,0,0},{39, 3,0,0},{39, 4,0,0},{39, 5,0,0},{39, 6,0,0},{39, 7,0,0},{39, 8,0,0},{39, 9,0,0},{39,10,0,0},{39,11,0,0},{39,12,0,0},{39,13,0,0},{39,14,0,0},{39,15,0,0},{39,16,0,0},{39,17,1,0},{39,18,0,0},{39,19,1,0},{39,20,0,0},{39,21,0,0},{39,22,0,0},{39,23,0,0},{39,24,0,0}},
	{{40, 2,0,0},{40, 3,0,0},{40, 4,0,0},{40, 5,0,0},{40, 6,0,0},{40, 7,0,0},{40, 8,0,0},{40, 9,0,0},{40,10,0,0},{40,11,0,0},{40,12,0,0},{40,13,0,0},{40,14,0,0},{40,15,1,0},{40,16,1,0},{40,17,1,0},{40,18,0,0},{40,19,1,0},{40,20,0,0},{40,21,0,0},{40,22,0,0},{40,23,0,0},{40,24,0,0}},
	{{41, 2,0,0},{41, 3,0,0},{41, 4,0,0},{41, 5,0,0},{41, 6,0,0},{41, 7,0,0},{41, 8,0,0},{41, 9,0,0},{41,10,0,0},{41,11,0,0},{41,12,0,0},{41,13,0,0},{41,14,0,0},{41,15,0,1},{41,16,0,0},{41,17,0,0},{41,18,0,0},{41,19,1,0},{41,20,0,0},{41,21,0,0},{41,22,0,0},{41,23,0,0},{41,24,0,0}},
	{{42, 2,0,0},{42, 3,0,0},{42, 4,0,0},{42, 5,0,0},{42, 6,0,0},{42, 7,0,0},{42, 8,0,0},{42, 9,0,0},{42,10,0,0},{42,11,0,0},{42,12,0,0},{42,13,0,0},{42,14,0,0},{42,15,0,1},{42,16,1,0},{42,17,1,0},{42,18,1,0},{42,19,1,0},{42,20,0,0},{42,21,0,0},{42,22,0,0},{42,23,0,0},{42,24,0,0}},
	{{43, 2,0,0},{43, 3,0,0},{43, 4,0,0},{43, 5,0,0},{43, 6,0,0},{43, 7,0,0},{43, 8,0,0},{43, 9,0,0},{43,10,0,0},{43,11,0,0},{43,12,0,0},{43,13,0,0},{43,14,0,0},{43,15,1,0},{43,16,1,0},{43,17,1,0},{43,18,1,0},{43,19,1,0},{43,20,0,0},{43,21,0,0},{43,22,0,0},{43,23,0,0},{43,24,0,0}},
	{{44, 2,0,0},{44, 3,0,0},{44, 4,0,0},{44, 5,0,0},{44, 6,0,0},{44, 7,0,0},{44, 8,0,0},{44, 9,0,0},{44,10,0,0},{44,11,0,0},{44,12,0,0},{44,13,0,0},{44,14,0,0},{44,15,0,0},{44,16,0,0},{44,17,0,0},{44,18,0,0},{44,19,0,0},{44,20,0,0},{44,21,0,0},{44,22,0,0},{44,23,0,0},{44,24,0,0}},
	{{45, 2,0,0},{45, 3,0,0},{45, 4,0,0},{45, 5,0,0},{45, 6,0,0},{45, 7,0,0},{45, 8,0,0},{45, 9,0,0},{45,10,0,0},{45,11,0,0},{45,12,0,0},{45,13,0,0},{45,14,0,0},{45,15,0,0},{45,16,0,0},{45,17,0,0},{45,18,0,0},{45,19,0,0},{45,20,0,0},{45,21,0,0},{45,22,0,0},{45,23,0,0},{45,24,0,0}},
	{{46, 2,0,0},{46, 3,0,0},{46, 4,0,0},{46, 5,0,0},{46, 6,0,0},{46, 7,0,0},{46, 8,0,0},{46, 9,0,0},{46,10,0,0},{46,11,0,0},{46,12,0,0},{46,13,0,0},{46,14,0,0},{46,15,0,0},{46,16,0,0},{46,17,0,0},{46,18,0,0},{46,19,0,0},{46,20,0,0},{46,21,0,0},{46,22,0,0},{46,23,0,0},{46,24,0,0}},
	{{47, 2,0,0},{47, 3,0,0},{47, 4,0,0},{47, 5,0,0},{47, 6,0,0},{47, 7,0,0},{47, 8,0,0},{47, 9,0,0},{47,10,0,0},{47,11,0,0},{47,12,0,0},{47,13,0,0},{47,14,0,0},{47,15,0,0},{47,16,0,0},{47,17,0,0},{47,18,0,0},{47,19,0,0},{47,20,0,0},{47,21,0,0},{47,22,0,0},{47,23,0,0},{47,24,0,0}},
	{{48, 2,0,0},{48, 3,0,0},{48, 4,0,0},{48, 5,0,0},{48, 6,0,0},{48, 7,0,0},{48, 8,0,0},{48, 9,0,0},{48,10,0,0},{48,11,0,0},{48,12,0,0},{48,13,0,0},{48,14,0,0},{48,15,0,0},{48,16,0,0},{48,17,0,0},{48,18,0,0},{48,19,0,0},{48,20,0,0},{48,21,0,0},{48,22,0,0},{48,23,0,0},{48,24,0,0}},
	{{49, 2,0,0},{49, 3,0,0},{49, 4,0,0},{49, 5,0,0},{49, 6,0,0},{49, 7,0,0},{49, 8,0,0},{49, 9,0,0},{49,10,0,0},{49,11,0,0},{49,12,0,0},{49,13,0,0},{49,14,0,0},{49,15,0,0},{49,16,0,0},{49,17,0,0},{49,18,0,0},{49,19,0,0},{49,20,0,0},{49,21,0,0},{49,22,0,0},{49,23,0,0},{49,24,0,0}},
	{{50, 2,0,0},{50, 3,0,0},{50, 4,0,0},{50, 5,0,0},{50, 6,0,0},{50, 7,0,0},{50, 8,0,0},{50, 9,0,0},{50,10,0,0},{50,11,0,0},{50,12,0,0},{50,13,0,0},{50,14,0,0},{50,15,0,0},{50,16,0,0},{50,17,0,0},{50,18,0,0},{50,19,0,0},{50,20,0,0},{50,21,0,0},{50,22,0,0},{50,23,0,0},{50,24,0,0}},
	{{51, 2,0,0},{51, 3,0,0},{51, 4,0,0},{51, 5,0,0},{51, 6,0,0},{51, 7,0,0},{51, 8,0,0},{51, 9,0,0},{51,10,0,0},{51,11,0,0},{51,12,0,0},{51,13,0,0},{51,14,0,0},{51,15,0,0},{51,16,0,0},{51,17,0,0},{51,18,0,0},{51,19,0,0},{51,20,0,0},{51,21,0,0},{51,22,0,0},{51,23,0,0},{51,24,0,0}},
	{{52, 2,0,0},{52, 3,0,0},{52, 4,0,0},{52, 5,0,0},{52, 6,0,0},{52, 7,0,0},{52, 8,0,0},{52, 9,0,0},{52,10,0,0},{52,11,0,0},{52,12,0,0},{52,13,0,0},{52,14,0,0},{52,15,0,0},{52,16,0,0},{52,17,0,0},{52,18,0,0},{52,19,0,0},{52,20,0,0},{52,21,0,0},{52,22,0,0},{52,23,0,0},{52,24,0,0}},
	{{53, 2,0,0},{53, 3,0,0},{53, 4,0,0},{53, 5,0,0},{53, 6,0,0},{53, 7,0,0},{53, 8,0,0},{53, 9,0,0},{53,10,0,0},{53,11,0,0},{53,12,0,0},{53,13,0,0},{53,14,0,0},{53,15,0,0},{53,16,0,0},{53,17,0,0},{53,18,0,0},{53,19,0,0},{53,20,0,0},{53,21,0,0},{53,22,0,0},{53,23,0,0},{53,24,0,0}},
	{{54, 2,0,0},{54, 3,0,0},{54, 4,0,0},{54, 5,0,0},{54, 6,0,0},{54, 7,0,0},{54, 8,0,0},{54, 9,0,0},{54,10,0,0},{54,11,0,0},{54,12,0,0},{54,13,0,0},{54,14,0,0},{54,15,0,0},{54,16,0,0},{54,17,0,0},{54,18,0,0},{54,19,0,0},{54,20,0,0},{54,21,0,0},{54,22,0,0},{54,23,0,0},{54,24,0,0}},
	{{55, 2,0,0},{55, 3,0,0},{55, 4,0,0},{55, 5,0,0},{55, 6,0,0},{55, 7,0,0},{55, 8,0,0},{55, 9,0,0},{55,10,0,0},{55,11,0,0},{55,12,0,0},{55,13,0,0},{55,14,0,0},{55,15,0,0},{55,16,0,0},{55,17,0,0},{55,18,0,0},{55,19,0,0},{55,20,0,0},{55,21,0,0},{55,22,0,0},{55,23,0,0},{55,24,0,0}},
	{{56, 2,0,0},{56, 3,0,0},{56, 4,0,0},{56, 5,0,0},{56, 6,0,0},{56, 7,0,0},{56, 8,0,0},{56, 9,0,0},{56,10,0,0},{56,11,0,0},{56,12,0,0},{56,13,0,0},{56,14,0,0},{56,15,0,0},{56,16,0,0},{56,17,0,0},{56,18,0,0},{56,19,0,0},{56,20,0,0},{56,21,0,0},{56,22,0,0},{56,23,0,0},{56,24,0,0}},
	{{57, 2,0,0},{57, 3,0,0},{57, 4,0,0},{57, 5,0,0},{57, 6,0,0},{57, 7,0,0},{57, 8,0,0},{57, 9,0,0},{57,10,0,0},{57,11,0,0},{57,12,0,0},{57,13,0,0},{57,14,0,0},{57,15,0,0},{57,16,0,0},{57,17,0,0},{57,18,0,0},{57,19,0,0},{57,20,0,0},{57,21,0,0},{57,22,0,0},{57,23,0,0},{57,24,0,0}},
	{{58, 2,0,0},{58, 3,0,0},{58, 4,0,0},{58, 5,0,0},{58, 6,0,0},{58, 7,0,0},{58, 8,0,0},{58, 9,0,0},{58,10,0,0},{58,11,0,0},{58,12,0,0},{58,13,0,0},{58,14,0,0},{58,15,0,0},{58,16,0,0},{58,17,0,0},{58,18,0,0},{58,19,0,0},{58,20,0,0},{58,21,0,0},{58,22,0,0},{58,23,0,0},{58,24,0,0}}
};
