#include "map.h"

#include "globals.h"
#include "graphics.h"

#define numBuck 10

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map[2];
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    return (map_width()*Y+X);
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    return key % numBuck; 
}

void maps_init()
{
    // TODO: Implement!    
    // Initialize hash table
    // Set width & height
    
    map[0].items = createHashTable(map_hash, numBuck);
    map[1].items = createHashTable(map_hash, numBuck);
    map[0].h = 50;
    map[0].w = 50; 
    map[1].h = 17;
    map[1].w = 17; 
}

Map* get_active_map()
{
    
    return &map[active_map];
}
int get_map() {
    return active_map;
}

Map* set_active_map(int m)
{
    active_map = m;
    return &map[active_map];
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    return map[active_map].w;
}

int map_height()
{
    return map[active_map].h;
}

int map_area()
{
    return (map[active_map].h * map[active_map].w);
}

MapItem* get_north(int x, int y)
{
    int newY = y-1;
    unsigned int key = XY_KEY(x, newY);
    return ((MapItem*) getItem(map[active_map].items, key));
}

MapItem* get_south(int x, int y)
{
    int newY = y+1;
    unsigned int key = XY_KEY(x, newY);
    return ((MapItem*) getItem(map[active_map].items, key));
}

MapItem* get_east(int x, int y)
{
    int newX = x+1;
    unsigned int key = XY_KEY(newX, y);
    return ((MapItem*) getItem(map[active_map].items, key));
}

MapItem* get_west(int x, int y)
{
    int newX = x-1;
    unsigned int key = XY_KEY(newX, y);
    return ((MapItem*) getItem(map[active_map].items, key));
}

MapItem* get_here(int x, int y)
{
    unsigned int key = XY_KEY(x, y);
    return ((MapItem*) getItem(map[active_map].items, key));
}


void map_erase(int x, int y)
{
    unsigned int key = XY_KEY(x, y);
    return deleteItem(map[active_map].items, key);
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}
void add_nWall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = NWALL;
        w1->draw = draw_nWall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_wizard(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WIZARD;
    w1->draw = draw_wizard;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val); // If something is already there, free it   
}
void add_door(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = DOOR;
    w1->draw = draw_door;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val);
}
    
void add_portal1(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WIZARD;
    w1->draw = draw_portal1;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val); // If something is already there, free it   
}
void add_portal2(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WIZARD;
    w1->draw = draw_portal2;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val); // If something is already there, free it   
}
void add_portal3(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WIZARD;
    w1->draw = draw_portal3;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val); // If something is already there, free it   
}
void add_portal4(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WIZARD;
    w1->draw = draw_portal4;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val); // If something is already there, free it   
}
void add_portal5(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = WIZARD;
    w1->draw = draw_portal5;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val); // If something is already there, free it   
}
void add_portal6(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PORTAL;
    w1->draw = draw_portal6;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), w1);
    if (val) free(val); // If something is already there, free it   
}


void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_plant2(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant2;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_grass(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GRASS;
    w1->draw = draw_grass;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_chest(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CHEST;
    w1->draw = draw_chest;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_key(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = KEY;
    w1->draw = draw_key;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_egg(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = EGG;
    w1->draw = draw_egg;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_egg2(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = EGG;
    w1->draw = draw_egg2;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_nether(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = NETHER;
    w1->draw = draw_nether;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_crystal(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CRYSTAL;
    w1->draw = draw_crystal;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}