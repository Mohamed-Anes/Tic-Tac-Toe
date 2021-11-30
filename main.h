#ifndef __MAIN_H__
#define __MAIN_H__


//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

//Screen dimension constants
/*static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;
static const Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN;*/



#define RUNNING 2
#define X_WIN 0
#define O_WIN 1
#define TIE 3

#define EMPTY 2
#define PLAYER_X 0
#define PLAYER_O 1


typedef struct {
    int turn;
    int game_state;
    }Player;




//Function definitions
void init();
SDL_Window *create_window();
SDL_Renderer *create_renderer(SDL_Window *win);
void pick_color(SDL_Renderer *renderer, SDL_Color my_color);
SDL_Rect create_rectangle(int x, int y, int w, int h);
void draw_circle(SDL_Renderer *rend, int x, int y, int R);
void draw_o(SDL_Renderer *rend, int x, int y);
void draw_x(SDL_Renderer *rend, int x, int y);
void draw_background(SDL_Renderer *rend);
void present_board(SDL_Renderer *rend);
int update_board(int x, int y, int turn);
int scan_board();
void erase_board();
void end_game(SDL_Renderer *rend, int game_state);

#endif // __MAIN_H__







