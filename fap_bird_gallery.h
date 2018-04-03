#ifndef GALLERY_H
#pragma once

#include "fap_bird_SDL.h"

SDL_Texture* upper_pipe = NULL;
SDL_Texture* lower_pipe = NULL;
SDL_Texture* back_ground = NULL;
SDL_Texture* ground = NULL;
SDL_Texture* upper_pipe_mouth = NULL;
SDL_Texture* lower_pipe_mouth = NULL;
SDL_Texture* bird = NULL;

SDL_Texture* pause_button = NULL;
SDL_Texture* replay_button = NULL;

SDL_Texture* score_board = NULL;

TTF_Font* font = NULL;

//
void load_gallery()
{
    upper_pipe = loadTexture( "media/images/upper_pipe.png" );
    lower_pipe = loadTexture( "media/images/lower_pipe.png" );
    back_ground = loadTexture( "media/images/background.png" );
    ground = loadTexture( "media/images/ground.png" );
    upper_pipe_mouth = loadTexture( "media/images/upper_pipe_mouth.png" );
    lower_pipe_mouth = loadTexture( "media/images/lower_pipe_mouth.png" );
    bird = loadTexture( "media/images/bird.png" );
    //
    replay_button = loadTexture( "media/images/restart.png" );
    pause_button = loadTexture( "media/images/pause.png" );
    //
    font = TTF_OpenFont( "flappy-bird.ttf", 75 );
    //
    score_board = loadTexture( "media/images/score_board.png" );
}

void destroy_gallery()
{
    SDL_DestroyTexture( upper_pipe );
    SDL_DestroyTexture( lower_pipe );
    SDL_DestroyTexture( back_ground );
    SDL_DestroyTexture( ground );
    SDL_DestroyTexture( upper_pipe_mouth );
    SDL_DestroyTexture( lower_pipe_mouth );
    SDL_DestroyTexture( bird );
    //
    SDL_DestroyTexture( pause_button );
    SDL_DestroyTexture( replay_button );
    //
    font = NULL;
    //
    SDL_DestroyTexture( score_board );
}
#endif // GALLERY_H
