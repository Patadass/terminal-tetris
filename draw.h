#include <windows.h>

#ifndef TETRIS_DRAW_H
#define TETRIS_DRAW_H

#define BACKGROUND_WHITE (BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE)
#define BACKGROUND_BLACK (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN)



class Draw{
private:
public:
    static HANDLE h_console;
    static BOOL setxy(short x, short y);
    static BOOL setxy(int x,int y);
    static void set_color(WORD w);
    static void reset_color();

    static void draw_fill_rect(int x, int y, int width,int height);
    static void draw_rect(int x,int y,int width,int height);

    static void draw_o_block(int x,int y,int width = 2,int height = 2);
};

#endif //TETRIS_DRAW_H
