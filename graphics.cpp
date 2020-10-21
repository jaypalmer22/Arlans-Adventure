#include "graphics.h"

#include "globals.h"
#include "map.h"



void draw_player(int u, int v, int key)
{
    if (!get_map()) {
        char player[122] =  "77866786766"
                            "86766666786"
                            "6666HHH6667"
                            "676HFFFH668"
                            "676HFFFH666"
                            "686H4F4H866"
                            "76644_44666"
                            "66644_44676"
                            "667F4J4F666"
                            "6666E8E6667"
                            "8768?6?6786";
        draw_img(u,v,player);
    } else {
        char player[122] =  "^^@||^@|^||"
                            "@|^|||||^@|"
                            "||||HHH|||^"
                            "|^|HFFFH||@"
                            "|^|HFFFH|||"
                            "|@|H4F4H@||"
                            "^||44_44|||"
                            "|||44_44|^|"
                            "||^F4J4F|||"
                            "||||E@E|||^"
                            "@^|@?|?|^@|";
        draw_img(u,v,player);
    }                          
} 

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if      (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == '[') colors[i] = MAGIC;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == '1') colors[i] = DSKIN;
        else if (img[i] == '2') colors[i] = MAROON;
        else if (img[i] == 'K') colors[i] = BLACK;
        else if (img[i] == 'A') colors[i] = WALL1;
        else if (img[i] == 'B') colors[i] = WALL2;
        else if (img[i] == 'C') colors[i] = WALL3;
        else if (img[i] == '%') colors[i] = MBROWN;
        else if (img[i] == 'P') colors[i] = PURPLE;
        else if (img[i] == 'L') colors[i] = LPURPLE;
        else if (img[i] == '~') colors[i] = DBROWN;
        else if (img[i] == '!') colors[i] = SBROWN;
        else if (img[i] == '6') colors[i] = GRASS1;
        else if (img[i] == '7') colors[i] = GRASS2;
        else if (img[i] == '8') colors[i] = GRASS3;
        else if (img[i] == '|') colors[i] = NETHER1;
        else if (img[i] == '^') colors[i] = NETHER2;
        else if (img[i] == '@') colors[i] = NETHER3;
        else if (img[i] == '&') colors[i] = NETHER4;
        else if (img[i] == '#') colors[i] = NETHER5;
        else if (img[i] == '$') colors[i] = NETHER6;
        else if (img[i] == '4') colors[i] = ROBE;
        else if (img[i] == '?') colors[i] = SHADOW;
        else if (img[i] == '_') colors[i] = BEARD;
        else if (img[i] == '`') colors[i] = SHAZAM;
        else if (img[i] == 'O') colors[i] = GOLD;
        else if (img[i] == 'E') colors[i] = PANTS;
        else if (img[i] == 'F') colors[i] = LSKIN;
        else if (img[i] == 'H') colors[i] = HAIR;
        else if (img[i] == 'J') colors[i] = BELT;
        
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    if (get_map()) {
    char nether[122] = "^^@||^@|^||"
                      "@|^|||||^@|"
                      "||||||@|||^"
                      "|^|@^|||||@"
                      "|^||||@^|||"
                      "|@|||||@@||"
                      "^||@^||||||"
                      "|||||||^|^|"
                      "||^@|||||||"
                      "|||||@^|||^"
                      "@^|@^|||^@|";
    draw_img(u,v,nether);
    } else {
    char grass[122] = "77866786766"
                      "86766666786"
                      "66666686667"
                      "67687666668"
                      "67666687666"
                      "68666668866"
                      "76687666666"
                      "66666667676"
                      "66786666666"
                      "66666876667"
                      "87687666786";
    draw_img(u,v,grass);
    }
}

void draw_wall(int u, int v)
{
    char wall[122] = "AAAAAACCCCC"
                     "CCCCCACBBBC"
                     "CBBBCABBBBB"
                     "BBBBBABBBBB"
                     "BBBAAAAAAAA"
                     "AAAABBBBABB"
                     "BBABCCAACBC"
                     "CCACCCACCCA"
                     "AAAACCACCAB"
                     "BBBACCACCAC"
                     "CCCACCAAAA";
    draw_img(u,v,wall);
}

void draw_portal1(int u, int v)
{
    char portal1[122] = "AAAAAAB%BBB"  
                        "BBBBBA%%%%%" 
                        "%%%CB%%%%%%" 
                        "%C%%%%PPPLL" 
                        "CC%%%PPPLLP"
                        "AA%%%PPLLPP"
                        "CBB%%LLLPPP" 
                        "CCC%%LPPPPP" 
                        "AAA%%PPPPPL" 
                        "BB%%%PPPPLL" 
                        "BB%%%PPLLLP"; 
    draw_img(u,v,portal1);
}
void draw_portal2(int u, int v)
{
    char portal2[122] = "A%%%%%%%%%B"
                        "%%%%%%%%%%%" 
                        "%PPPPPLPPP%" 
                        "PPPPPLLPPPP" 
                        "PPPPLLPPPPP"
                        "PPLLLPPPPPL" 
                        "PLLPPPPPPLL" 
                        "LLPPPPLLLLP"
                        "LPPPPLLPPPP" 
                        "PPPLLLPPPPP" 
                        "PPLLPPPPPPL"; 
    draw_img(u,v,portal2);
}
void draw_portal3(int u, int v)
{
    char portal3[122] = "AAA%%ABBB%B"  
                        "%%%%BABC%%B" 
                        "%%%%%AC%%CC" 
                        "PPPP%%%%%%%"
                        "LLLPP%%%%%A"
                        "LPPPP%%%ABB" 
                        "PPPPP%%%ACB" 
                        "PPPPP%%%CCC" 
                        "PPLLLP%%CCA" 
                        "PLLPPP%%CCA"
                        "LLPPPP%%AAA"; 
    draw_img(u,v,portal3);
}
void draw_portal4(int u, int v)
{
    char portal4[122] = "AA%%%LLLPPP"  
                        "BB%%%PPPPPL" 
                        "BC%%%PPPPLL" 
                        "CC%%PPPPLLP" 
                        "CC%%PLLLPPP"
                        "AA%%LLPPPPP"
                        "CB%%PPPPPLL" 
                        "C%%%~PPPLLP" 
                        "A%%%~~PLPPP" 
                        "B%%%%~~~~~~" 
                        "%%%%%%%!!!!"; 
    draw_img(u,v,portal4);
}
void draw_portal5(int u, int v)
{
    char portal5[122] = "PLLPPPPPLLL"  
                        "LLPPPPLLLPP" 
                        "PPPPLLLPPPP" 
                        "PPPLLPPPPPL" 
                        "PPLLPPPPPLL"
                        "LLPPPPPPLLP"
                        "LPPPPPLLLPP" 
                        "PPPPLLLPPPP" 
                        "PPLLLPPPPPL" 
                        "~~~~~~~~~~~" 
                        "!!!!!!!!!!!"; 
    draw_img(u,v,portal5);
}
void draw_portal6(int u, int v)
{
    char portal6[122] = "PPPPPP%%BBB"  
                        "PPLLL%%%%CB" 
                        "LLLPPP%%%CC" 
                        "LPPPPPP%%CC" 
                        "PPPPPLL%%AA"
                        "PPPPLLP%%BB"
                        "PPLLLPP%%CB" 
                        "PLLPPP~%%%C" 
                        "LLPPP~~%%%A" 
                        "~~~~~~%%%%A" 
                        "~~~~~~%%%%A"; 
    draw_img(u,v,portal6);
}


void draw_plant(int u, int v)
{
    char plant[122] = "77866K86766"
                      "8676K3K6786"
                      "6666K3K6667"
                      "676K333K668"
                      "676K333K666"
                      "68K33333K66"
                      "76K33333K66"
                      "6K3333333K6"
                      "6K3333333K6"
                      "K333333333K"
                      "KKKKKKKKKKK";
    draw_img(u,v,plant);
}
void draw_plant2(int u, int v)
{
    char plant2[122] = "^^@||K@|^||"
                       "@|^|K3K|^@|"
                       "||||K3K|||^"
                       "|^|K333K||@"
                       "|^|K333K|||"
                       "|@K33333K||"
                       "^|K33333K||"
                       "|K3333333K|"
                       "|K3333333K|"
                       "K333333333K"
                       "KKKKKKKKKKK";
                      
    draw_img(u,v,plant2);
}
void draw_door(int u, int v)
{
    char door[122] =  "77866786766"
                      "86766666786"
                      "66666686667"
                      "67687666668"
                      "OOOOOOOOOOO"
                      "OOOOOOOOOOO"
                      "OOOOOOOOOOO"
                      "66666667676"
                      "66786666666"
                      "66666876667"
                      "87687666786";
    draw_img(u,v,door);
}
void draw_key(int u, int v)
{
    char key[122] =  "^^@||^@|^||"
                     "@|^|||||^@|"
                     "||||||@|||^"
                     "|^|@^|||||@"
                     "|^||||```||"
                     "|@`````@`||"
                     "^|`@`|```||"
                     "|||||||^|^|"
                     "||^@|||||||"
                     "|||||@^|||^"
                     "@^|@^|||^@|";
    draw_img(u,v,key);
}


void draw_chest(int u, int v)
{
    char chest[122] = "77KKKKKKK66"
                      "8KK%%%%%KK6"
                      "KK%%%O%%%KK"
                      "KKKKOOOKKKK"
                      "K%%%OOO%%%K"
                      "K%%%OOO%%%K"
                      "K%%%OOO%%%K"
                      "K%%%%%%%%%K"
                      "KOO%%%%%OOK"
                      "KOO%%%%%OOK"
                      "KKKKKKKKKKK";
    draw_img(u,v,chest);
}
void draw_grass(int u, int v)
{
    char grass[122] = "77866786766"
                      "86766666786"
                      "66666686667"
                      "67687666668"
                      "67666687666"
                      "68666668866"
                      "76687666666"
                      "66666667676"
                      "66786666666"
                      "66666876667"
                      "87687666786";
    draw_img(u,v,grass);
                      
}
void draw_egg2(int u, int v)
{
    char egg2[122] = "7786KKK6766"
                     "867KOOOK786"
                     "66KOOOOOK67"
                     "6KOOOOOOOK8"
                     "6KOOOOOOOK6"
                     "KOOOOOOOOOK"
                     "KOOOOOOOOOK"
                     "KOOOOOOOOOK"
                     "6KOOOOOOOK6"
                     "66KKOOOKK67"
                     "8768KKK6786";
    draw_img(u,v,egg2);
}

void draw_crystal(int u, int v)
{
    char crystal[122] = "77866K86766"
                        "8676K[K6786"
                        "666K[[[K667"
                        "67K[[[[[K68"
                        "6K[[[[[[[K6"
                        "K[[[[[[[[[K"
                        "7K[[[[[[[K6"
                        "66K[[[[[K76"
                        "667K[[[K666"
                        "6666K[K6667"
                        "87687K66786";
    draw_img(u,v,crystal);
                      
}
void draw_egg(int u, int v)
{
    char egg[122] =    "^^@|KKK|^||"
                       "@|^KOOOK^@|"
                       "||KOOOOOK|^"
                       "|KOOOOOOOK@"
                       "|KOOOOOOOK|"
                       "KOOOOOOOOOK"
                       "KOOOOOOOOOK"
                       "KOOOOOOOOOK"
                       "|KOOOOOOOK|"
                       "||KKOOOKK|^"
                       "@^|@KKK|^@|";
    draw_img(u,v,egg);
}

void draw_nether(int u, int v)
{
    char nether[122] = "^^@||^@|^||"
                      "@|^|||||^@|"
                      "||||||@|||^"
                      "|^|@^|||||@"
                      "|^||||@^|||"
                      "|@|||||@@||"
                      "^||@^||||||"
                      "|||||||^|^|"
                      "||^@|||||||"
                      "|||||@^|||^"
                      "@^|@^|||^@|";
    draw_img(u,v,nether);
}
void draw_nWall(int u, int v)
{
    char nWall[122] = "&&&&&&$$$$$"
                      "$$$$$&$###$"
                      "$###$&#####"
                      "#####&#####"
                      "###&&&&&&&&"
                      "&&&&####&##"
                      "##&#$$&&$#$"
                      "$$&$$$&$$$&"
                      "&&&&$$&$$&#"
                      "###&$$&$$&$"
                      "$$$&$$&&&&";
    draw_img(u,v,nWall);
}

void draw_upper_status(int x, int y, int crystals)
{
    // Draw bottom border of status bar
    uLCD.filled_rectangle(0,8,128,0,0x87CEFA);
    uLCD.line(0, 8, 128, 8, RED);
    
    // Text Background color and color
    uLCD.textbackground_color(0x87CEFA);
    uLCD.color(0x8B0000);
    uLCD.text_width(1);
    uLCD.text_height(1);
    
    // Print the coords 
    uLCD.locate(0,0);
    uLCD.printf("(%d,",x);
    uLCD.locate(4,0);
    uLCD.printf("%d)",y);
    uLCD.locate(7,0);
    uLCD.printf("Crystals: %d", crystals);
}


void draw_lower_status(int h)
{
    uLCD.line(0, 120, 128, 120, BLACK);
    switch (h) {
        
        case 5:
            uLCD.filled_rectangle(0,128,128,120,GREEN);
            uLCD.color(0x8B0000);
            break;
        case 4:
            uLCD.filled_rectangle(0,128,102,120,GREEN);
            uLCD.filled_rectangle(103,128,128,120,RED);
            break;
        case 3:
            uLCD.filled_rectangle(0,128,76,120,GREEN);
            uLCD.filled_rectangle(77,128,128,120,RED);
            break;
        case 2:
            uLCD.filled_rectangle(0,128,50,120,GREEN);
            uLCD.filled_rectangle(51,128,128,120,RED);
            break;
        case 1:
            uLCD.filled_rectangle(0,128,25,120,GREEN);
            uLCD.filled_rectangle(26,128,128,120,RED);
            break;
        case 0:
            uLCD.filled_rectangle(0,128,128,120,RED);
            break;
    }
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

void draw_wizard(int u, int v)
{
    char wizard[122] = "77866786766"
                       "86766666[8["
                       "6666___66[7"
                       "676_~~__6!8"
                       "6764~4__6!6"
                       "6864_46_446"
                       "7644_4446!6"
                       "66644`476!6"
                       "667444466!6"
                       "666644466!7"
                       "876844467!6";
    draw_img(u,v,wizard);
}

