#include <iostream>
#include <cstdlib>
#include <time.h>

#include "fap_bird_gameplay.h"

using namespace std;

int main( int argc, char* args[] )
{
    srand(time(NULL));

    init_SDL( "FAP BIRD", SCREEN_WIDTH, SCREEN_HEIGHT );
    TTF_Init();
    Mix_Init( MIX_INIT_MP3 );
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    bool quit = false;
    bool restart = true;

    load_gallery();
    load_sound_pack();

    SDL_Event event;
    while ( restart )
    {
        quit = false;
        reset_rect();
        start_screen( event, quit );
        int score = gameplay( event, quit );
        restart = score_board_and_replay_button_animation( score, event, quit );
    }
    destroy_gallery();
    destroy_sound_pack();

    close_SDL();
    TTF_Quit();
    Mix_Quit();

    return 0;
}

