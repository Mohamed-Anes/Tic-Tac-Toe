#include "main.h"


int main(int argc, char* args[])
{
    init();
    SDL_Window *win = create_window();
    SDL_Renderer *rend = create_renderer(win);
    SDL_Event event;

    Player player = {.turn = PLAYER_X, .game_state = RUNNING};

    draw_background(rend);

    int quit = 0;
    do{
        SDL_PollEvent(&event);
        present_board(rend);
        switch(event.type){
        case SDL_MOUSEBUTTONDOWN :
            if(update_board(event.button.x, event.button.y, player.turn) == 0){
                player.turn = !player.turn;
                }
            //present_board(rend);
            player.game_state = scan_board();
            if(player.game_state != RUNNING){
                end_game(rend, player.game_state);
                }
            break;

        case SDL_QUIT :
            quit = 1;
            break;

            }


        }while(!quit);



    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    printf("%d", player.game_state);
    return 0;
}
