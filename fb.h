#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* FrameBuffer Colors*/
#define FB_BLACK 0
#define FB_BLUE 1
#define FB_GREEN 2
#define FB_CYAN 3
#define FB_RED 4
#define FB_MAGENTA 5
#define FB_BROWN 6
#define FB_LIGHT_GREY 7
#define FB_DARK_GREY 8
#define FB_LIGHT_BLUE 9
#define FB_LIGHT_GREEN 10
#define FB_LIGHT_CYAN 11
#define FB_LIGHT_RED 12
#define FB_LIGHT_MAGENTA 13
#define FB_LIGHT_BROWN 14
#define FB_WHITE 15

/* fb points to the start of framebuffer */
char *fb = (char *) 0x000B8000;

/* global cursor position */
unsigned short GLOBAL_CURSOR = 0x0;

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
    GLOBAL_CURSOR = pos;
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}


/* fb_write:
* Writes a char *buf of length len at the current cursor position
*
*  @param *buf  Char buffer to write to framebuffer
*  @param len   Len of the character buffer
*/
void fb_write(char *buf, unsigned int len){
    unsigned short itr = 2*GLOBAL_CURSOR;

    for(unsigned int i=0; i<len; i++){
        fb_move_cursor(GLOBAL_CURSOR);
        fb_write_cell(itr, buf[i], FB_GREEN, FB_DARK_GREY);
        GLOBAL_CURSOR += 0x01;
        itr += 0x02;
    }
    fb_move_cursor(GLOBAL_CURSOR);
}


/* fb_clear:
* Clears the framebuffer to the given background
*
*   @param BG  Background colour
*/
void fb_clear(unsigned short BG){
    GLOBAL_CURSOR = 0;
    for(unsigned short i = 0; i<80*50; i+=2){
        fb_write_cell(i, ' ', BG, FB_WHITE);
    }
}
