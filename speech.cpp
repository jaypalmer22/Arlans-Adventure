#include "speech.h"
#include "graphics.h"

#include "globals.h"
#include "hardware.h"

GameInputs in2;
Timer waitTime;
int toggle = 0;

/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
//static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line);

/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();

void draw_speech_bubble()
{
    uLCD.filled_rectangle(0, 114 , 128, 74, 0xFFFFFF); //big purple rectangle

    //border of bubble
    uLCD.filled_rectangle(0,    74, 128,  76, 0x000000); // Top
    uLCD.filled_rectangle(0,   114, 128, 112, 0x000000); // Bottom

    uLCD.filled_rectangle(0,    114,   2, 74, 0x000000); // Left
    uLCD.filled_rectangle(128,  114, 126, 74, 0x000000); // Right
}

//void erase_speech_bubble()
//{
//}

void draw_speech_line(const char* line)
{
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.color(BLACK);
    int len = strlen(line);
    while (*line)

    {
        uLCD.locate(1,10);
        draw_speech_bubble();
        for (int i = 0; i < 17 && *line; i++) {
            uLCD.printf("%c", *line);
            wait_ms(40);
            line++;
        }
        uLCD.locate(1,11);
        for(int j = 17; j < 34 && *line; j++) {
            uLCD.printf("%c", *line);
            wait_ms(40);
            line++;
        }
        uLCD.locate(1,12);
        for(int k = 34; k < 51 && *line; k++) {
            uLCD.printf("%c", *line);
            wait_ms(40);
            line++;
        }
         speech_bubble_wait();
    }
    //if(len > 36) speech_bubble_wait();
    //else 
    //wait_ms(250);
}

void speech_bubble_wait()
{
    waitTime.start();
    int timePass;

    do {
        // wait until ~1.5 seconds pass before being able to remove
        in2 = read_inputs();
        timePass = waitTime.read_ms();

        wait_ms(250);
        toggle = !toggle;
        if (toggle) uLCD.filled_circle(120,121,4,PURPLE);
        else uLCD.filled_circle(120,121,4,BLACK);
        in2 = read_inputs();
    } while(in2.b3 || !(timePass > 500 && !in2.b3));

    uLCD.filled_circle(120,121,4,BLACK);
    return;
}

void speech(const char* line1)
{
    draw_speech_bubble();
    draw_speech_line(line1);;
    //erase_speech_bubble();
}

//void long_speech(const char* lines[], int n)
//{
//}
