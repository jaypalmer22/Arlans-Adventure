#ifndef GRAPHICS_H
#define GRAPHICS_H

//Define colors
#define YELLOW  0xFFFF00
#define BROWN   0xDEB887
#define DIRT    BROWN
#define FOREST  0x228B22 
#define MAGIC   0x3386A5
#define WHITE   0xFFFFFF
#define DSKIN   0x8B4513
#define MAROON  0x800000
#define BLACK   0x000000
#define WALL1   0x494943
#define WALL2   0xA5A594
#define WALL3   0x7A7880
#define PURPLE  0x692564
#define LPURPLE 0x7A2B74
#define MBROWN  0x8C5C4D
#define SBROWN  0x7B5143
#define DBROWN  0x613F35
#define GRASS1  0x66A14E
#define GRASS2  0x6BA952
#define GRASS3  0x7BAC55
#define NETHER1 0x453D56
#define NETHER2 0x524966
#define NETHER3 0x5F4D6F
#define NETHER4 0x271443 
#define NETHER5 0x52254F
#define NETHER6 0x7E6190
#define ROBE    0x451212
#define SHADOW  0x2E0C0C
#define BEARD   0xB3B3B3
#define SHAZAM  0xEEC32C
#define GOLD    0xFFDF00
#define PANTS   0x124460
#define LSKIN   0xF7B072
#define HAIR    0xAF853D
#define BELT    0xE59131

/**
 * Draws the player. This depends on the player state, so it is not a DrawFunc.
 */
void draw_player(int u, int v, int key);

/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions. 
 * These can be used as the MapItem draw functions.
 */
void draw_nothing(int u, int v);
void draw_wall(int u, int v);
void draw_plant(int u, int v);
void draw_plant2(int u, int v);
void draw_grass(int u, int v);
void draw_wizard(int u, int v);
void draw_portal1(int u, int v);
void draw_portal2(int u, int v);
void draw_portal3(int u, int v);
void draw_portal4(int u, int v);
void draw_portal5(int u, int v);
void draw_portal6(int u, int v);
void draw_nether(int u, int v);
void draw_nWall(int u, int v);
void draw_door(int u, int v);
void draw_crystal(int u, int v);
void draw_chest(int u, int v);
void draw_key(int u, int v);
void draw_egg(int u, int v);
void draw_egg2(int u, int v);

/**
 * Draw the upper status bar.
 */
void draw_upper_status(int x, int y, int crystals);

/**
 * Draw the lower status bar.
 */ 
void draw_lower_status(int h);

/**
 * Draw the border for the map.
 */
void draw_border();
// New draw functions


#endif // GRAPHICS_H