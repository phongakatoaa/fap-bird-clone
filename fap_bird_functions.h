#ifndef FUNCTIONS_H
#pragma once

#include "fap_bird_data.h"
#include "fap_bird_gallery.h"
#include <string>
#include <algorithm>
#include <fstream>
//some calculate function here
void get_bird_height( SDL_Rect* bird_rect, const int falling_time, double& speed ) { //calculate bird's height base on gravitational formula
    if ( bird_rect->y >= SCREEN_HEIGHT ) return;
    speed = -jump_speed + gravity_force * falling_time; // v = v0 + g * t
    bird_rect->y += speed; //bird's falling
}
//
//
bool pipe_collistion_detected( SDL_Rect* bird_rect,
                                SDL_Rect* upper_pipe, SDL_Rect* upper_mouth,
                                SDL_Rect* lower_pipe, SDL_Rect* lower_mouth ) // check if the bird touched the pipes
{
    if ( SDL_HasIntersection( bird_rect, upper_pipe ) ) return true;
    if ( SDL_HasIntersection( bird_rect, upper_mouth ) ) return true;
    if ( SDL_HasIntersection( bird_rect, lower_pipe ) ) return true;
    if ( SDL_HasIntersection( bird_rect, lower_mouth ) ) return true;
    return false;
}
//
//
bool ground_collision_detected( SDL_Rect* bird_rect, SDL_Rect* ground_rect ) //check if the bird touchede the ground
{
    if ( SDL_HasIntersection( bird_rect, ground_rect ) ) return true;
    return false;
}
//
//
void get_angle( const double speed, int& angle ) //get bird's texture rotating angle
{
    if ( speed <= 5 ) { angle = -30; return; }
    if ( speed > 5 && speed < 10 ) { angle = 0; return; }
    if ( speed >= 10 && speed < 15 ) { angle = 15; return; }
    if ( speed >= 15 && speed < 20 ) { angle = 30; return; }
    if ( speed >= 20 && speed < 25 ) { angle = 45; return; }
    if ( speed >= 25 ) { angle = 90; return; }
}
//
//
std::string int_to_string ( int num ) //use to get score's text
{
    std::string convert;
    int mod;
    do
    {
        mod = num % 10;
        num /= 10;
        switch ( mod )
        {
        case 0: convert += "0"; break;
        case 1: convert += "1"; break;
        case 2: convert += "2"; break;
        case 3: convert += "3"; break;
        case 4: convert += "4"; break;
        case 5: convert += "5"; break;
        case 6: convert += "6"; break;
        case 7: convert += "7"; break;
        case 8: convert += "8"; break;
        case 9: convert += "9"; break;
        default: break;
        }
    } while ( num > 0 );
    reverse( convert.begin(), convert.end() );
    return convert;
}
//
//
int get_score( int& score, SDL_Rect* bird_rect,
            SDL_Rect* first_upper_pipe_rect, SDL_Rect* second_upper_pipe_rect ) //get player score as the bird passes pipes
{
    if ( bird_rect->x - first_upper_pipe_rect->x - pipe_width == pixel_jump )
        { score++; Mix_PlayChannel( -1, score_sound, 0); } //increase score and play scored sound
    if ( bird_rect->x - second_upper_pipe_rect->x - pipe_width == pixel_jump )
        { score++; Mix_PlayChannel( -1, score_sound, 0 ); }
    return score;
}
//
//some render functions here: pipes, ground
void render_pipes ( int& upper_pipe_height,
                   SDL_Rect* upper_pipe_rect, SDL_Rect* lower_pipe_rect,
                   SDL_Rect* upper_mouth_rect, SDL_Rect* lower_mouth_rect )
{
    if ( upper_pipe_rect->x == -pipe_width )
    {
        upper_pipe_rect->x = SCREEN_WIDTH;
        upper_pipe_height = random_pipe_height;
    }
    upper_pipe_rect->x -= pixel_jump;
    upper_pipe_rect->y = 0;
    upper_pipe_rect->h = upper_pipe_height - pipe_mouth_height;

    upper_mouth_rect->x = upper_pipe_rect->x;
    upper_mouth_rect->y = upper_pipe_rect->h;

    lower_pipe_rect->x = upper_pipe_rect->x;
    lower_pipe_rect->y = upper_pipe_height + width_between_pipes + pipe_mouth_height;
    lower_pipe_rect->h = SCREEN_HEIGHT - ground_height - upper_pipe_height - width_between_pipes - pipe_mouth_height;

    lower_mouth_rect->x = upper_pipe_rect->x;
    lower_mouth_rect->y = lower_pipe_rect->y - pipe_mouth_height;

    SDL_RenderCopy( renderer, upper_pipe, NULL, upper_pipe_rect );
    SDL_RenderCopy( renderer, upper_pipe_mouth, NULL, upper_mouth_rect );
    SDL_RenderCopy( renderer, lower_pipe, NULL, lower_pipe_rect );
    SDL_RenderCopy( renderer, lower_pipe_mouth, NULL, lower_mouth_rect );
}
//
void render_ground( SDL_Rect* first_ground, SDL_Rect* second_ground ) //render ground function, including ground animation
{
    if ( first_ground->x == -SCREEN_WIDTH ) first_ground->x = SCREEN_WIDTH;
    if ( second_ground-> x == -SCREEN_WIDTH ) second_ground->x = SCREEN_WIDTH;

    first_ground->x -= pixel_jump;
    second_ground->x -= pixel_jump;
    /*here i use two ground images
    in order to create an infinite ground animation
    as one replace another continously
    */
    SDL_RenderCopy( renderer, ground, NULL, first_ground );
    SDL_RenderCopy( renderer, ground, NULL, second_ground );
}
//
//
void render_environment()
{
    // render background
    SDL_RenderCopy( renderer, back_ground, NULL, &back_ground_rect );
    //render pipes
    render_pipes( first_upper_pipe_height, &first_upper_pipe_rect,
                &first_lower_pipe_rect, &first_upper_mouth_rect, &first_lower_mouth_rect );
    render_pipes( second_upper_pipe_height, &second_upper_pipe_rect,
                &second_lower_pipe_rect, &second_upper_mouth_rect, &second_lower_mouth_rect );
    //render ground
    render_ground( &first_ground_rect, &second_ground_rect );
}
//
//
void render_bird( int& falling_time, double& speed, int& angle, const int score )
{
    get_bird_height( &bird_rect, falling_time, speed );
    get_angle( speed, angle );
    SDL_RenderCopyEx( renderer, bird, NULL, &bird_rect, angle, NULL, SDL_FLIP_NONE );
}
void render_score( const int score )
{
    text_surface = TTF_RenderText_Solid( font, int_to_string( score ).c_str(), text_color );
    text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
    text_rect = { ( SCREEN_WIDTH - text_surface->w ) / 2, 30, text_surface->w, text_surface->h };
    SDL_RenderCopy( renderer, text_texture, NULL, &text_rect );
}
//
//
void render_gameplay( int& falling_time, double& speed, int& angle, const int score ) //all render functions in one function
{
    SDL_RenderClear( renderer ); // clear screen
    //environment
    render_environment();
    //render bird
    render_bird( falling_time, speed, angle, score );
    //render score
    render_score( score );
}
//
//
void update_screen()
{
    SDL_RenderPresent( renderer );
}
//
//
void render_score_board_text( int score )
{
    //get high score from file
    int high_score;
    //open file
    std::ifstream file ( "high score.txt" );
    //get high score
    file >> high_score;
    //close file
    file.close();
    //score text
    text_surface = TTF_RenderText_Solid( font, "SCORE:", text_color );
    //
    text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
    //
    text_rect = { ( SCREEN_WIDTH - text_surface->w / 2 ) / 2 , score_board_rect.y + 30, text_surface->w/2, text_surface->h/2 };
    //
    SDL_RenderCopy( renderer, text_texture, NULL, &text_rect );
    //render player's score
    text_surface = TTF_RenderText_Solid( font, int_to_string( score ).c_str(), text_color );
    //
    text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
    //
    text_rect = { ( SCREEN_WIDTH - text_surface->w / 2 ) / 2, score_board_rect.y + 60, text_surface->w / 2, text_surface->h / 2 };
    //
    SDL_RenderCopy( renderer, text_texture, NULL, &text_rect );
    //best score text
    text_surface = TTF_RenderText_Solid( font, "BEST:", text_color );
    //
    text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
    //
    text_rect = { ( SCREEN_WIDTH - text_surface->w / 2 ) / 2 , score_board_rect.y + 100, text_surface->w/2, text_surface->h/2 };
    //high score
    SDL_RenderCopy( renderer, text_texture, NULL, &text_rect );
    //
    text_surface = TTF_RenderText_Solid( font, int_to_string( high_score ).c_str(), text_color );
    //
    text_texture = SDL_CreateTextureFromSurface( renderer, text_surface );
    //
    text_rect = { ( SCREEN_WIDTH - text_surface->w / 2 ) / 2 , score_board_rect.y + 130, text_surface->w/2, text_surface->h/2 };
    //
    SDL_RenderCopy( renderer, text_texture, NULL, &text_rect );
    //overwrite score
    if ( score > high_score ) {
        //open file
        std::ofstream overwrite( "high score.txt" );
        //write new score
        overwrite << score;
        //close file
        overwrite.close();
    }
}
//
//
bool score_board_and_replay_button_animation( int score, SDL_Event& event, bool& quit )
{
    //restart flag
    bool restart = false;
    //waiting flag
    bool waiting = true;
    //mouse rect
    SDL_Rect mouse_rect;
    //render loop
    do {
        mouse_rect = { event.button.x, event.button.y, 10, 10 };
        while ( SDL_PollEvent( &event ) != 0 )
        {
            if ( event.type == SDL_QUIT ) quit = true;
            if ( (event.type == SDL_MOUSEBUTTONDOWN && SDL_HasIntersection( &mouse_rect, &replay_button_rect ) )
                || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) )
            {
                waiting = false;
                restart = true;
            }
        }
        //clear renderer
        SDL_RenderClear( renderer );
        //environment
        render_environment();
        //score board and restart button descend animation
        //calculate rect's height
        if ( score_board_rect.y < 100 ) score_board_rect.y += 3 * pixel_jump;
        if ( replay_button_rect.y < 325 ) replay_button_rect.y += 3 * pixel_jump;
        //update renderer
        SDL_RenderCopy( renderer, score_board, NULL, &score_board_rect );
        SDL_RenderCopy( renderer, replay_button, NULL, &replay_button_rect );
        //render score board text
        render_score_board_text( score );
        //SDL_RenderCopy()
        update_screen();
        //jump to next frame
        SDL_Delay( frame_jump_delay );
    } while ( waiting && !quit );
    //
    return restart;
}

//
void reset_rect()
{
    first_upper_pipe_rect = { SCREEN_WIDTH, 0, pipe_width, 0 };
    first_lower_pipe_rect = { 0, 0, pipe_width, 0 };
    first_upper_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
    first_lower_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
    //
    //
    second_upper_pipe_rect = { SCREEN_WIDTH + distance_between_two_pipes, 0, pipe_width, 0 };
    second_lower_pipe_rect = { 0, 0, pipe_width, 0 };
    second_upper_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
    second_lower_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
    //
    //
    bird_rect = { 150, 200, 50, 40 };
    //
    score_board_rect = { ( SCREEN_WIDTH - score_board_width ) / 2, -score_board_height - 200, score_board_width, score_board_height };
    //
    replay_button_rect = { ( SCREEN_WIDTH - replay_button_width ) / 2, -replay_button_height, replay_button_width, replay_button_height };
}
//
//

#endif // FUNCTIONS_H
