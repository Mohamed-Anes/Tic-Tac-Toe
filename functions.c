#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const Uint32 WINDOW_FLAGS =  SDL_WINDOW_SHOWN;

SDL_Color RED = {255, 0, 0, 255};
SDL_Color GREEN = {0, 255, 0, 255};
SDL_Color BLUE = {0, 0, 255, 255};
SDL_Color WHITE = {255, 255, 255, 255};
SDL_Color BLACK = {0, 0, 0, 255};

#define EMPTY 2
#define PLAYER_X 0
#define PLAYER_O 1

#define RUNNING 2
#define X_WIN 0
#define O_WIN 1
#define TIE 3


int board[9] = {EMPTY, EMPTY, EMPTY,
                EMPTY, EMPTY, EMPTY,
                EMPTY, EMPTY, EMPTY};




void init(){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "Error SDL_Init : %s",SDL_GetError());
        return -1;
        }
    }

SDL_Window *create_window(){
    SDL_Window *win = SDL_CreateWindow("my SDL learning project",
                                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_FLAGS);
    if(win == NULL){
        fprintf(stderr, "Error SDL_Window : %s",SDL_GetError());
        return -1;
    }
    return win;
    }

SDL_Renderer *create_renderer(SDL_Window *win){
    SDL_Renderer *rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    if(rend == NULL){
        fprintf(stderr, "Error SDL_Renderer : %s",SDL_GetError());
        return -1;
        }
    }

void pick_color(SDL_Renderer *rend, SDL_Color my_color){
    SDL_SetRenderDrawColor(rend, my_color.r, my_color.g, my_color.b, my_color.a);
    }

SDL_Rect create_rectangle(int x, int y, int w, int h){
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    return rect;
    }

void draw_circle(SDL_Renderer *rend, int x, int y, int R){

    SDL_Point points[R + 1];

    for(int i = 0; i <= R; ++i){
        points[i].x = x + i;
        points[i].y = y + sqrt(R*R - (i*i));
        }
    SDL_RenderDrawLines(rend, points, R + 1);

    for(int i = 0; i <= R; ++i){
        points[i].x = x - i;
        points[i].y = y + sqrt(R*R - (i*i));
        }
    SDL_RenderDrawLines(rend, points, R + 1);

    for(int i = 0; i <= R; ++i){
        points[i].x = x + i;
        points[i].y = y - sqrt(R*R - (i*i));
        }
    SDL_RenderDrawLines(rend, points, R + 1);

    for(int i = 0; i <= R; ++i){
        points[i].x = x - i;
        points[i].y = y - sqrt(R*R - (i*i));
        }
    SDL_RenderDrawLines(rend, points, R + 1);

    }

void draw_o(SDL_Renderer *rend, int x, int y){
    pick_color(rend, BLUE);
    for(int i = 0; i < 10; ++i){
        draw_circle(rend, x, y, 70 + i);
        }
    }

void draw_x(SDL_Renderer *rend, int x, int y){
    pick_color(rend, RED);
    for(int i = 0; i < 10; ++i){
        SDL_RenderDrawLine(rend, x-50+i, y-50-i, x+i+50, y-i+50);
        }
    for(int i = 0; i < 10; ++i){
        SDL_RenderDrawLine(rend, x-50+i, y+50+i, x+i+50, y+i-50);
        }
    }

void draw_background(SDL_Renderer *rend){
    pick_color(rend, WHITE);
    SDL_RenderClear(rend);
    pick_color(rend, BLACK);
    for(int i = 1; i < 3; ++i){
        SDL_RenderDrawLine(rend, SCREEN_WIDTH/3 * i, 0, SCREEN_WIDTH/3 * i, SCREEN_HEIGHT);
        SDL_RenderDrawLine(rend, 0, SCREEN_HEIGHT/3 * i, SCREEN_WIDTH, SCREEN_HEIGHT/3 * i);
        }
    }

void present_board(SDL_Renderer *rend){
    draw_background(rend);
    for(int i = 0; i < 9; ++i){
        if(board[i] == PLAYER_O){
            draw_o(rend, SCREEN_WIDTH/6 * (2*(i%3) + 1), SCREEN_HEIGHT/6 * (2*(i/3) + 1));
            }
        if(board[i] == PLAYER_X){
            draw_x(rend, SCREEN_WIDTH/6 * (2*(i%3) + 1), SCREEN_HEIGHT/6 * (2*(i/3) + 1));
            }
        }
    SDL_RenderPresent(rend);
    }

int update_board(int x, int y, int turn){
    int i = (x / (SCREEN_WIDTH / 3)) + 3*(y / (SCREEN_HEIGHT / 3));
    if(board[i] != EMPTY){
        return -1;
        }
    if(turn == PLAYER_O){
        board[i] = PLAYER_O;
        }
    else{
        board[i] = PLAYER_X;
        }
    return 0;
    }

int scan_board(){
    //checking for winner or tie
    int i, counter = 0;

    for(i = 0; i < 3; ++i){
        //checking horizontals
        if((board[3*i] != EMPTY) && (board[3*i] == board[3*i + 1]) && (board[3*i + 1] == board[3*i + 2])){
            return board[i];
            }
        //checking verticals
        if((board[3*i] != EMPTY) && (board[i] == board[3 + i]) && (board[3 + i] == board[6 + i])){
            return board[i];
            }
    }
    if(board[0] == board[4] && board[4] == board[8]){
        return board[0];
        }
    if(board[2] == board[4] && board[4] == board[6]){
        return board[2];
        }

    for(i = 0; i < 9; ++i){
        if(board[i] != EMPTY){
            ++counter;
            }
        }
    if(counter == 9){
        return TIE;
        }
    return RUNNING;
    }

void erase_board(){
    for(int i = 0; i < 9; ++i){
        board[i] = EMPTY;
        }
    }

void end_game(SDL_Renderer *rend, int game_state){
    for(int i = 0; i < 9; ++i){
        board[i] = game_state;
        }

    present_board(rend);
    SDL_RenderPresent(rend);
    SDL_Delay(1000);
    erase_board();
    }

