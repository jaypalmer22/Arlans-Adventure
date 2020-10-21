// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Declared Variables
GameInputs inputs;
int action;
int update;
int omni = 0;
int quest = 0;
int health = 5;
int hit = 0;
int crystal = 0;
int found1 = 0;
int found2 = 0;
int found3 = 0;
int found4 = 0;
int found5 = 0;
double stars = 1;
int eggs = 0;
int start = 1;
int first = 0;

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
int main ();

int move(int x, int y, int action);
int go_north(int x, int y);
int go_south(int x, int y);
int go_east(int x, int y);
int go_west(int x, int y);
void near(int x, int y);
void draw_start();


/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
int get_action(GameInputs inputs)
{
    char *Tips = "To move, tilt theboard. To open   the menu hold    Button 2. To talkor push/pick up  items press      Button 3.";
    if (first == 0) {
        wait(.5);
        speech(Tips);
        first = 1;
    }
    if (inputs.ax >= .35)
        return GO_DOWN;
    if (inputs.ay >= .35)
        return GO_RIGHT;
    if (inputs.ax < -.35)
        return GO_UP;
    if (inputs.ay < -.35)
        return GO_LEFT;
    if (!inputs.b1) {
        wait(1);
        omni = !omni;
        //pc.printf("Omni: %d", omni);
    }
    if (!inputs.b3) {
        wait(1);
        return ACTION_BUTTON;
    }
    if (!inputs.b2) {
        wait(.5);
        return MENU_BUTTON;
    }
    
    return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 3
#define FULL_DRAW 2
#define OPEN_MENU 4
int update_game(int action)
{
    if (health == 0) {
        Player.x = 30;
        Player.y = 28;
        health = 5;
    } 
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP:
            if (move(Player.px, Player.py, action))
                return FULL_DRAW;
            else  
                break;
        case GO_LEFT:   
            if (move(Player.px, Player.py, action))
                return FULL_DRAW;
            else
                break;            
        case GO_DOWN: 
            if (move(Player.px, Player.py, action))
                return FULL_DRAW; 
            else 
                break;
        case GO_RIGHT:  
            if (move(Player.px, Player.py, action))
                return FULL_DRAW;
            else 
                break;
        case ACTION_BUTTON: 
            if ((Player.y == 13) && ((Player.x == 30) || (Player.x == 32) || (Player.x == 34) || (Player.x == 36) || (Player.x == 38))) {
                if (Player.x == 38) {
                    stars++;
                    char *correct = "Arlan drinks the potion and feels life flow throughhis veins. Good  choice!";
                    speech(correct);
                } else if ((Player.x == 32) || (Player.x == 36)) {
                    char *wine = "Arlan takes a    sip... just wine.";
                    speech(wine);
                    wait(2);
                    stars -= .5;;
                    break;
                } else {
                    stars = 0;
                    char *poison = "Arlan takes a sipand begins to    feel weak. He    collapses and    everything goes  black.";
                    speech(poison);
                }      
                wait(2);
                return GAME_OVER;
            } else {
                wait(.5);
                near(Player.x, Player.y);
                break;
            }
        case MENU_BUTTON: 
            return OPEN_MENU;
        default:        break;
    }
    return NO_RESULT;
}
void near(int x, int y)
{
    
    if ((x == 33 && y == 26) || ((y == 25) && ((x == 32) || (x == 34)))) {
        if (!quest) {
            char *getQuest = "GANDALF: Hello   there traveler.  You look lost. Ifyou wish to      return home, I   may know a way.";
            char *getQuest2 = "Within this      chamber lies the tresure that manyhave seeked, but none have found.";
            char *getQuest3 = "This treasure hasthe power to     grant it's user  to go wherever   they please. The journey will not be easy. First   you must traversethe maze of Myra.Travel westward  to begin your    journey."; 
            speech(getQuest);
            speech(getQuest2);
            speech(getQuest3);
            add_grass(25,29);
            add_grass(25,30);
            quest = 1;
        } else if (quest == 1) {
            char *gotQuest = "GANDALF: Travel  westward to beginthe first task.  Hurry, time is of the essence.";
            speech(gotQuest);
            wait(2);
        } else if (quest == 3) {
            char *finalQuest = "GANDALF: Wow, I'mhappy to see you alive. I've taken a liking to you  young traveler.";
            char *finalQuest2 = "Take the key and head into the     chamber. To     complete the     final task, you  will need the    Riddle of the    Ancients.";
            char *finalQuest3 = "It is as follows:";
            char *finalQuest4 = "Five chests lie  here and wait.   They will decide your fate. One   will let you moveahead."
                                "Two of     poison will kill you instead. Two hold wine are notbad nor good.";
            char *finalQuest5 = "Here are your    clues:"; 
            char *finalQuest6 = "1. Each poison   lies on the left of each wine.";
            char *finalQuest7 = "2. A liar would  say, the first   chest is fine.";
            char *finalQuest8 = "3. Number 4 is   different than 1.";
            char *finalQuest9 = "If you need the  clues again,     visit the menu.";
            speech(finalQuest);
            speech(finalQuest2);
            speech(finalQuest3);
            speech(finalQuest4);
            speech(finalQuest5);
            speech(finalQuest6);
            speech(finalQuest7);
            speech(finalQuest8);
            speech(finalQuest9);
            quest = 4;                  
        }
            
    }
    if ((x == 14 && y == 22) || ((y == 23) && ((x == 13) || (x == 15)))) {
        if (quest == 1) {
            char *quest2a = "AMBROSE: Hello,  you must be      seeking          Winterfell's     treasure. I      assume Gandalf   sent you. I see  you have         completed the    maze, quite       impressive.";
            char *quest2b = "The journey will only grow more   difficult. Your  next quest is to retrieve the key.Head the to the  top left and     venture into the Shadow realm.    Good luck young  traveler.";
            speech(quest2a);
            speech(quest2b);
            quest = 2;
        }
    }
    if ((y == 2) && (x == 1 || x == 2 || x == 3)) {
        if (crystal >= 3) {
            if ((!get_map()) || (!(Player.has_key)))
                set_active_map(!(get_map()));
            else {
                set_active_map(!(get_map()));
                Player.x = 30;
                Player.y = 28;
            }
        } else {
            char *portalF = "To power the     portal, collect 3 crystals of    essence";
            speech(portalF);
            wait(2);
        }
    }
    if ((x == 2) && (y == 23) && (!found1)) {
        char *crystals = "You have found a crystal!";
        speech(crystals);
        add_grass(1,23);
        crystal++;
        found1 = 1;
        wait(1);
    }
    if ((x == 2) && (y == 48) && (!found2)) {
        char *crystals = "You have found a crystal!";
        speech(crystals);
        add_grass(1,48);
        crystal++;
        found2 = 1;
        wait(1);
    }
    if ((x == 11) && (y == 42) && (!found3)) {
        char *crystals = "You have found a crystal!";
        speech(crystals);
        add_grass(10,42);
        crystal++;
        found3 = 1;
        wait(1);
    }
    if ((x == 20) && (y == 16) && (!found4)) {
        char *crystals = "You have found a crystal!";
        speech(crystals);
        add_grass(20,17);
        crystal++;
        found4 = 1;
        wait(1);
    }
    if ((x == 12) && (y == 28) && (!found5)) {
        char *crystals = "You have found a crystal!";
        speech(crystals);
        add_grass(11,28);
        crystal++;
        found5 = 1;
        wait(1);
    }            
 
    if (((y == 25) && ((x == 35) || (x == 36) || (x == 37)))) {
        if ((quest == 4) && (Player.has_key)) {
            char *unlock = "The door unlocked!";
            speech(unlock);
            wait(1.5);
            add_grass(35,24);
            add_grass(36,24);
            add_grass(37,24);
        } else if ((quest == 3) && (Player.has_key)) {
            char *unlock2 = "Talk to Gandalf  before you enter!";
            speech(unlock2);
            wait(1.5);
        } else {
            char *unlock3 = "The door is       locked!";
            speech(unlock3);
            wait(1.5);
        }
    }
    if ((x == 48) && (y == 2) && eggs <= 3) {
        char *Egg = "This item seems  valuable...";
        speech(Egg);
        eggs++;
        add_grass(48,1);
        wait(1.5);
    }
    if ((x == 48) && (y == 47) && eggs <= 3) {
        char *Egg = "This item seems  valuable...";
        speech(Egg);
        eggs++;
        add_grass(48,48);
        wait(1.5);
    }
    if (get_map()) {
        if ((x == 2) && (y == 4)) {
            add_wall(2,6,HORIZONTAL,1);
            add_nether(2,5);
            char *move = "The block moved!";
            speech(move);
            wait(2);
        } 
        if ((x == 5) && (y == 5)) {
            add_wall(7,5,HORIZONTAL,1);
            add_nether(6,5);
            wait(1);
        } 
        if ((x == 6) && (y == 6)) {
            add_wall(6,8,HORIZONTAL,1);
            add_nether(6,7);
            wait(1);
        } 
        if ((x == 3) && (y == 13)) {
            add_wall(3,15,HORIZONTAL,1);
            add_nether(3,14);
            wait(1);
        } 
        if ((x == 5) && (y == 15)) {
            add_wall(7,15,HORIZONTAL,1);
            add_nether(6,15);
            wait(1);
        } 
        if ((x == 6) && (y == 15)) {
            add_wall(6,13,HORIZONTAL,1);
            add_nether(6,14);
            wait(1);
        } 
        if ((x == 11) && (y == 13)) {
            add_wall(11,15,HORIZONTAL,1);
            add_nether(11,14);
            wait(1);
        } 
        if ((x == 11) && (y == 14)) {
            add_wall(13,14,HORIZONTAL,1);
            add_nether(12,14);
            wait(1);
        } 
        if ((x == 12) && (y == 14)) {
            add_wall(12,12,HORIZONTAL,1);
            add_nether(12,13);
            wait(1);
        }
        if ((x == 14) && (y == 13) && (Player.has_key == 0))  {
            char *Key = "You found the    key! Time to headback and talk to Ganfalf.";
            speech(Key);
            Player.has_key = 1;
            add_nether(15,13);
            wait(1.5);
            quest = 3;
        }
        if ((x == 15) && (y == 2) && eggs <= 3) {
            char *Egg = "This item seems  valuable...";
            speech(Egg);
            eggs++;
            add_nether(15,1);
            wait(1.5);
        } 
    }
        
}
int move(int x, int y, int action) 
{
    MapItem *item;
    switch (action)
    {
        case GO_UP:
            item = get_north(x,y);
            if (item->walkable || omni) {
                Player.y--;
                if (item->type == PLANT) {
                    health--;
                    wait(1);
                }
                return 1;
            } else 
                return 0;
        case GO_DOWN:
            item = get_south(x,y);
            if (item->walkable || omni) {
                Player.y++;
                if (item->type == PLANT) {
                    health--;
                    wait(1);
                }
                return 1;
            } else 
                return 0;
        case GO_LEFT:
            item = get_west(x,y);
            if (item->walkable || omni) {
                Player.x--;
                if (item->type == PLANT) {
                    health--;
                    wait(1);
                }
                return 1;
            } else 
                return 0;
        case GO_RIGHT:
            item = get_east(x,y);
            if (item->walkable || omni) {
                Player.x++;
                if (item->type == PLANT) {
                    health--;
                    wait(1);
                }
                return 1;
            } else 
                return 0;
    }
    return 0;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    if (init == 3) {
        if (crystal == 4)
            stars += .5;
        if (crystal == 5)
            stars += 1;
        if (eggs == 1)
            stars += .5;
        if (eggs == 2)
            stars += .25;
        if (eggs == 3)
            stars += .25;
        uLCD.filled_rectangle(0,0,255,255,NETHER2);
        uLCD.locate(1,2);
        uLCD.textbackground_color(NETHER2);
        uLCD.text_width(2);
        uLCD.text_height(2);
        uLCD.color(GOLD);
        uLCD.printf("THE END");
        uLCD.locate(2,5);
        uLCD.text_height(1.5);
        uLCD.text_width(1.5);
        uLCD.color(WHITE);
        uLCD.locate(1,7);
        uLCD.printf("Score:    %.1f/4.0", stars);
        uLCD.locate(1,8);
        uLCD.printf("Eggs:     %d/3", eggs);
        uLCD.locate(1,9);
        uLCD.printf("Crystals: %d/5", crystal);
        wait(10000000000000);
    }
    if (init == 4) {
        if (quest != 4) {
            uLCD.filled_rectangle(12,16,112,112,GOLD);
            uLCD.filled_rectangle(12,16,112,16,BLACK);
            uLCD.filled_rectangle(12,16,12,112,BLACK);
            uLCD.filled_rectangle(112,16,112,112,BLACK);
            uLCD.filled_rectangle(12,112,112,112,BLACK);
            uLCD.textbackground_color(GOLD);
            uLCD.text_underline(ON);
            uLCD.color(BLACK);
            uLCD.text_height(1);
            uLCD.text_string("MENU", 6, 3, FONT_7X8, BLACK);
            uLCD.text_height(1);
            uLCD.text_underline(OFF);
            uLCD.text_bold(ON);
            uLCD.text_string("Controls", 2, 4, FONT_7X8, BLACK);
            uLCD.text_underline(OFF);
            uLCD.circle(24,51,7,BLACK);
            uLCD.text_string("Omni Mode", 5, 6, FONT_7X8, BLACK);
            uLCD.text_string("Menu (Hold)", 5, 8, FONT_7X8, BLACK);
            uLCD.text_string("Action", 5, 10, FONT_7X8, BLACK);
            uLCD.circle(24,67,7,BLACK);
            uLCD.circle(24,83,7,BLACK);
            uLCD.text_char('1',3,6,BLACK);
            uLCD.text_char('2',3,8,BLACK);
            uLCD.text_char('3',3,10,BLACK);
            uLCD.text_string("Quest:", 2, 12, FONT_7X8, BLACK);
            if (quest == 0)
                uLCD.text_string("None", 6, 12, FONT_7X8, BLACK);
            else if (quest == 1) {
                uLCD.text_string("(1)Maze", 8, 12, FONT_7X8, BLACK);
                uLCD.text_string("of Myra", 8, 13, FONT_7X8, BLACK);
            }
            else if (quest == 2) {
                uLCD.text_string("(2)Power", 8, 12, FONT_7X8, BLACK); 
                uLCD.text_string("the Portal", 8, 13, FONT_7X8, BLACK);
            }
            else if (quest == 3) {
                uLCD.text_string("(3)The", 6, 12, FONT_7X8, BLACK);
                uLCD.text_string("Final Task", 6, 13, FONT_7X8, BLACK);
            }
            wait(.5);
            while (!inputs.b2) {
                inputs = read_inputs();
            }
        } else {
            uLCD.filled_rectangle(4,16,120,112,GOLD);
            uLCD.filled_rectangle(4,16,120,16,BLACK);
            uLCD.filled_rectangle(4,16,12,112,BLACK);
            uLCD.filled_rectangle(120,16,120,112,BLACK);
            uLCD.filled_rectangle(4,112,120,112,BLACK);
            uLCD.textbackground_color(GOLD);
            uLCD.text_string("2 Poison,2 Wine", 2, 2, FONT_7X8, BLACK);
            uLCD.text_string("Clues: ", 2, 3, FONT_7X8, BLACK);
            uLCD.text_string("1. Each posion", 2, 4, FONT_7X8, BLACK);
            uLCD.text_string("lies left of", 2, 5, FONT_7X8, BLACK);
            uLCD.text_string("each wine.", 2, 6, FONT_7X8, BLACK);
            uLCD.text_string("2. A liar would", 2, 7, FONT_7X8, BLACK);
            uLCD.text_string("say the first", 2, 8, FONT_7X8, BLACK);
            uLCD.text_string("chest is fine", 2, 9, FONT_7X8, BLACK);
            uLCD.text_string("3. Number 4", 2, 10, FONT_7X8, BLACK);
            uLCD.text_string("is different", 2, 11, FONT_7X8, BLACK);
            uLCD.text_string("than 1", 2, 12, FONT_7X8, BLACK);
            while (!inputs.b2) {
                inputs = read_inputs();
            }
        }
    }
        
    
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                draw_player(u, v, Player.has_key);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                if (!get_map())
                draw = draw_wall;
                else
                draw = draw_nWall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
            
        }
    }

    // Draw status bars    
    draw_upper_status(Player.x, Player.y, crystal);
    draw_lower_status(health);
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // Add grass (bg 1)
    // "Random" plants
    char *Start = "During the night,young Arlan      dreams that he   warps to another dimension. Beforehe knows it, he  awakens to find  himself at       Winterfell Castle"
                 "An old wizard    beckons him to   approach.        Hesistant but    longing for some answers, Arlan   approaches. And  so the adventure begins...";
    speech(Start);
    uLCD.filled_rectangle(0,0,128,128,BLACK);
    wait(1.5); 
    draw_start();
    Map* map = set_active_map(0);
       
    
    
   
    add_wizard(33,25);
    add_wizard(14,23);

    
    pc.printf("plants\r\n");
        
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    add_wall(1,              24,             HORIZONTAL, 10);
    add_wall(14,             24,             HORIZONTAL, 21);
    add_wall(39,             24,             HORIZONTAL, 10);  
    add_wall(38,             24,             HORIZONTAL, 11);
    add_wall(25,             1,              VERTICAL,  28);
    add_wall(25,             31,             VERTICAL,  17);
    //Maze
    add_wall(3,29,HORIZONTAL,13);
    add_wall(3,42,VERTICAL,5);
    add_wall(3,32,VERTICAL,7);
    add_wall(3,32,HORIZONTAL,4);
    add_wall(3,41,HORIZONTAL,3);
    add_wall(6,33,VERTICAL,9);
    add_wall(6,44,VERTICAL,5);
    add_wall(10,25,VERTICAL,4);
    add_wall(9,30,VERTICAL,4);
    add_wall(10,33,HORIZONTAL,6);
    add_wall(7,36,HORIZONTAL,11);
    add_wall(9,37,VERTICAL,7);
    add_wall(10,43,HORIZONTAL,6);
    add_wall(15,44,VERTICAL,2);
    add_wall(9,46,HORIZONTAL,13);
    add_wall(12,37,VERTICAL,3);
    add_wall(12,40,HORIZONTAL,6);
    add_wall(18,25,VERTICAL,16);
    add_wall(19,28,HORIZONTAL,6);
    add_wall(18,43,HORIZONTAL,7);
    add_wall(21,31,VERTICAL,12);
    add_door(35,24);
    add_door(36,24);
    add_door(37,24);
    add_door(25,29);
    add_door(25,30);
    add_plant(19,34);
    add_plant(20,38);
    add_plant(16,41);
    add_plant(11,42);
    add_plant(20,44);
    add_plant(21,48);
    add_plant(14,47);
    add_plant(8,48);
    add_plant(7,43);
    add_plant(4,47);
    add_plant(2,41);
    add_plant(1,35);
    add_plant(6,31);
    add_plant(13,34);
    add_plant(17,32);
    add_plant(16,34);
    add_plant(9,35);
    add_plant(8,32);
    add_plant(2,33);
    add_plant(12,48);
    add_plant(20,31);
    add_plant(1,22);
    add_plant(2,22);
    add_plant(20,18);
    add_plant(21,18);
    add_plant(19,18);
    add_plant(19,17);
    add_plant(21,17);
    add_plant(19,16);
    add_plant(21,16);
    add_plant(10,41);
    add_plant(11,27);
    add_plant(47,48);
    add_plant(47,1);
    add_crystal(1,23);
    add_crystal(1,48);
    add_crystal(10,42);
    add_crystal(20,17);
    add_crystal(11,28);
    add_chest(30,12);
    add_chest(32,12);
    add_chest(34,12);
    add_chest(36,12);
    add_chest(38,12);
    add_egg2(48,48);
    add_egg2(48,1);
    
                                
    pc.printf("Walls done!\r\n");
    add_portal1(1,0);
    add_portal2(2,0);
    add_portal3(3,0);
    add_portal4(1,1);
    add_portal5(2,1);
    add_portal6(3,1);

    print_map();
}
void init_second_map()
{
    // Add grass (bg 1)
    // "Random" plants
    Map* map = set_active_map(1);
    pc.printf("Adding grass./n");
   
    pc.printf("plants\r\n");
        
    pc.printf("Adding walls!\r\n");
    add_nWall(0,              0,              HORIZONTAL, map_width());
    add_nWall(0,              map_height()-1, HORIZONTAL, map_width());
    add_nWall(0,              0,              VERTICAL,   map_height());
    add_nWall(map_width()-1,  0,              VERTICAL,   map_height());    
    add_nWall(5,1,VERTICAL,3);
    add_nWall(1,4,VERTICAL,1);
    add_nWall(1,6,VERTICAL,1);
    add_nWall(3,4,HORIZONTAL,5);
    add_nWall(3,6,HORIZONTAL,3);
    add_nWall(7,6,VERTICAL,2);
    add_nWall(8,6,VERTICAL,4);
    add_nWall(5,8,VERTICAL,1);
    add_nWall(4,8,VERTICAL,6);
    add_nWall(1,10,VERTICAL,1);
    add_nWall(2,10,VERTICAL,4);
    add_nWall(1,14,VERTICAL,1);
    add_nWall(5,13,VERTICAL,1);
    add_nWall(7,13,VERTICAL,1);
    add_nWall(13,15,VERTICAL,1);
    add_nWall(14,14,HORIZONTAL,2);
    add_nWall(13,12,HORIZONTAL,3);
    add_nWall(5,10,HORIZONTAL,10);
    add_wall(2,5,HORIZONTAL,1);
    add_wall(6,5,HORIZONTAL,1);
    add_wall(6,7,HORIZONTAL,1);
    add_wall(3,14,HORIZONTAL,1);
    add_wall(6,14,VERTICAL,2);
    add_wall(11,14,HORIZONTAL,2);
    add_wall(12,13,HORIZONTAL,1); 
    add_plant2(2,8);
    add_plant2(3,8);
    add_plant2(5,14);
    add_plant2(9,14);
    add_plant2(9,15);
    add_plant2(9,11);
    add_plant2(9,12);
    add_plant2(14,1); 
    add_key(15,13); 
    add_egg(15,1);  
                           
    pc.printf("Walls done!\r\n");
    add_portal1(1,0);
    add_portal2(2,0);
    add_portal3(3,0);
    add_portal4(1,1);
    add_portal5(2,1);
    add_portal6(3,1);
    

    print_map();
}
void draw_start()
{
    if (start == 1) {
        start = 0;
        inputs = read_inputs();
        uLCD.textbackground_color(BLACK);
        char *startText = "WARP:ARLAN'S ADVENTURE";
        char *bottomText = "By: Jason Palmer";
        
        while (*startText) {
            uLCD.locate(4,1);
            uLCD.color(NETHER2);
            uLCD.text_width(2);
            uLCD.text_height(2);
            for (int i = 0; i < 5; i++) {
                uLCD.printf("%c", *startText);
                wait_ms(50);
                startText++;
            }
            uLCD.locate(1,2);
            uLCD.color(GOLD);
            uLCD.text_width(2);
            uLCD.text_height(2);
            for(int j = 5; j < 13 && *startText; j++) {
                uLCD.printf("%c", *startText);
                wait_ms(50);
                startText++;
            }
            uLCD.locate(0,4);
            uLCD.color(GOLD);
            uLCD.text_width(2);
            uLCD.text_height(2);
            for(int k = 14; k < 23 && *startText; k++) {
                uLCD.printf("%c", *startText);
                wait_ms(50);
                startText++;
            }
            uLCD.locate(0,7);
            uLCD.color(MAGIC);
            uLCD.text_width(1);
            uLCD.text_height(1);
            for(int x = 0; x < 16; x++) {
                uLCD.printf("%c", *bottomText);
                wait_ms(50);
                bottomText++;
            }
            uLCD.locate(0,12);
            uLCD.color(WHITE);
            uLCD.printf("To begin press '3'");
    
        }
        while (inputs.b3) {
            inputs = read_inputs();
        }
    }
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    // Initialize the maps
    maps_init();
    init_main_map();
    init_second_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = 30;
    Player.y = 28;

    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actuall do the game update:
        // 1. Read inputs   
        inputs = read_inputs();     
        // 2. Determine action (get_action)
        action = get_action(inputs);        
        // 3. Update game (update_game)
        update = update_game(action);
        // 3b. Check for game over
        // 4. Draw frame (draw_game)
        draw_game(update);
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
}
