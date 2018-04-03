#ifndef GAMEPLAY_H
#pragma once

#include "fap_bird_functions.h"
#include <iostream>
//
//
void death_animation( SDL_Event& event, int& falling_time, double& speed, int& angle )
{
    //reset renderer to NULL
    SDL_RenderClear( renderer );
    //update null screen
    update_screen();
    //count as a frame
    SDL_Delay( frame_jump_delay );
    //some lines are just the same as above
    falling_time = 0;
    //increase bird falling speed
    speed = -jump_speed;
    //render death animation as the bird falls off the screen
    do {
        //keep rendering gameplay but no access to input devices
        render_gameplay( falling_time, speed, angle, 0 );
        //update screen
        update_screen();
        //jump to next frame
        SDL_Delay( frame_jump_delay );
        //get bird's falling time
        falling_time += frame_jump_delay;
    } while ( bird_rect.y < SCREEN_HEIGHT ); //when the bird's out of the screen
}
//
//
int gameplay( SDL_Event& event, bool& quit/*play loop flag*/ )
{

    int falling_time = 0; //millisecond
    double speed = 0; //bird falling speed
    int angle = 0; //bird texture's rotating angle
    int score = 0; //player's score obviously
    //play loop
    bool lost = false;

    while ( !lost && !quit )
    {
        //handle event
        while ( SDL_PollEvent( &event ) != 0 )
        {
            if ( event.type == SDL_QUIT ) quit = true; //quit game
            //pause game by esc button
            if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) {
                while ( SDL_WaitEvent(&event) != 0 ) {
                    //press esc button again to continue the game
                    if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) break;
                }
            }
            //if player press the left mouse button or space key the bird jump
            if ( event.type == SDL_MOUSEBUTTONDOWN || ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE ) ) {
                reset_tick; //reset the bird's falling time
                speed = -jump_speed; //reset the bird's speed to its max ( bird jump )

                Mix_PlayChannel( -1, wing_sound, 0 );// play bird's going-up sound ( bad english )
            }
        }
        //render screen while playing
        render_gameplay( falling_time, speed, angle, score );
        //update screen
        update_screen();
        //if lose condition happened, show death animation then end the play loop
        if ( full_ground_collsion_detected || first_pipe_collision_detected || second_pipe_collision_detected ) //lose condition
        {
            //play collision sound
            Mix_PlayChannel( -1, hit_sound, 0 );
            //make the screen go white so that the player realize he/she has lost
            //clear the renderer
            SDL_RenderClear( renderer );
            //update screen with null renderer
            SDL_RenderPresent( renderer );
            //death animation
            death_animation( event, falling_time, speed, angle );
            //end play loop
            lost = true;
        }
        //get player_score
        score = get_score( score, &bird_rect, &first_upper_pipe_rect, &second_upper_pipe_rect );
        //jump to next frame
        SDL_Delay( frame_jump_delay );
        //get bird's falling time
        falling_time += frame_jump_delay;
    }
    return score;
}

void start_screen( SDL_Event& event, bool& quit )
{
    //render game title surface
    text_surface = TTF_RenderText_Solid( font, "Flappy Bird", text_color );
    //create texture from surface pixels
    text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
    //get text texture rectangle
    text_rect = { ( SCREEN_WIDTH - text_surface->w ) / 2, 50, text_surface->w, text_surface->h };
    //same lines for second text
    second_text_surface = TTF_RenderText_Solid( font, "press any key to play", text_color );
    //
    second_text_texture = SDL_CreateTextureFromSurface( renderer, second_text_surface );
    //
    second_text_rect = { text_rect.x, 350, second_text_surface->w/2, second_text_surface->h/2 };
    //
    bool start = false; //start screen loop flag

    while ( !start ) {
        //handle event
        //player presses any key to start game
        while ( SDL_PollEvent( &event ) != 0 ) {
            if ( event.type == SDL_QUIT ) { quit = true; return; }
            if ( event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN )
            {
                start = true;
                Mix_PlayChannel( -1, wing_sound, 0 );//bird's first jumping sound
            }
        }
        //render ground
        render_ground( &first_ground_rect, &second_ground_rect );
        //render background
        SDL_RenderCopy( renderer, back_ground, NULL, &back_ground_rect );
        //render game title
        SDL_RenderCopy( renderer, text_texture, NULL, &text_rect );
        //render instruction text
        SDL_RenderCopy( renderer, second_text_texture, NULL, &second_text_rect );
        //render the bird
        SDL_RenderCopyEx( renderer, bird, NULL, &bird_rect, 0, NULL, SDL_FLIP_NONE );
        //update screen
        SDL_RenderPresent( renderer );
        //delay time before next frame
        SDL_Delay( frame_jump_delay );
    }
//
}


#endif // GAMEPLAY_H

