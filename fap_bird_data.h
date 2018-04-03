#ifndef DATA_H
#pragma once

#include "fap_bird_SDL.h"
#include <SDL2/SDL_mixer.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 550
#define width_between_pipes 125
#define pipe_mouth_height 40
#define pipe_width 70
#define ground_height 60
#define pixel_jump 5
#define frame_jump_delay 45
#define upper_pipe_min 50
#define upper_pipe_max SCREEN_HEIGHT - ground_height - upper_pipe_min - width_between_pipes
#define distance_between_two_pipes 230
#define gravity_force 0.05 // pixel/ms^2
#define jump_speed 15
#define score_board_height 200
#define score_board_width 150
#define replay_button_width 150
#define replay_button_height 60

#define random_pipe_height rand()% ( upper_pipe_max - upper_pipe_min ) + upper_pipe_min

#define reset_tick falling_time = 0

#define full_ground_collsion_detected ground_collision_detected( &bird_rect, &first_ground_rect ) || ground_collision_detected( &bird_rect, &second_ground_rect )

#define first_pipe_collision_detected pipe_collistion_detected( &bird_rect, &first_upper_pipe_rect, &first_upper_mouth_rect, &first_lower_pipe_rect, &first_lower_mouth_rect )

#define second_pipe_collision_detected pipe_collistion_detected( &bird_rect, &second_upper_pipe_rect, &second_upper_mouth_rect, &second_lower_pipe_rect, &second_lower_mouth_rect )

//all images' rectangle stored here
//
SDL_Rect first_ground_rect = { 0, SCREEN_HEIGHT - ground_height, SCREEN_WIDTH, ground_height };
SDL_Rect second_ground_rect = { SCREEN_WIDTH, SCREEN_HEIGHT - ground_height, SCREEN_WIDTH, ground_height };
//
//
SDL_Rect back_ground_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - ground_height };
//
//
SDL_Rect first_upper_pipe_rect = { SCREEN_WIDTH, 0, pipe_width, 0 };
SDL_Rect first_lower_pipe_rect = { 0, 0, pipe_width, 0 };
SDL_Rect first_upper_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
SDL_Rect first_lower_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
//
//
SDL_Rect second_upper_pipe_rect = { SCREEN_WIDTH + distance_between_two_pipes, 0, pipe_width, 0 };
SDL_Rect second_lower_pipe_rect = { 0, 0, pipe_width, 0 };
SDL_Rect second_upper_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
SDL_Rect second_lower_mouth_rect = { 0, 0, pipe_width, pipe_mouth_height };
//
//
SDL_Rect bird_rect = { 150, 200, 10, 10 };
//
SDL_Rect score_board_rect = { ( SCREEN_WIDTH - score_board_width ) / 2, -score_board_height - 200, score_board_width, score_board_height };
//
SDL_Rect replay_button_rect = { ( SCREEN_WIDTH - replay_button_width ) / 2, -replay_button_height, replay_button_width, replay_button_height };
//pipes' height ( random after each dissappearing )
int first_upper_pipe_height = rand() % random_pipe_height;
int second_upper_pipe_height = rand() % random_pipe_height;
//
//text's color, font and rectangle
SDL_Color text_color = {255,0,127,0}; //color black
//
SDL_Surface* text_surface = NULL;
//
SDL_Texture* text_texture = NULL;
//
SDL_Surface* second_text_surface = NULL;
//
SDL_Texture* second_text_texture = NULL;
//
SDL_Rect text_rect;
//
SDL_Rect second_text_rect;
//
//some game's sounds here
Mix_Chunk* die_sound = NULL;
Mix_Chunk* hit_sound = NULL;
Mix_Chunk* score_sound = NULL;
Mix_Chunk* wing_sound = NULL;
//
void load_sound_pack()
{
    die_sound = Mix_LoadWAV( "sounds/sfx_die.wav" );
    hit_sound = Mix_LoadWAV( "sounds/sfx_hit.wav" );
    score_sound = Mix_LoadWAV( "sounds/sfx_point.wav" );
    wing_sound = Mix_LoadWAV( "sounds/sfx_wing.wav" );
}
//
void destroy_sound_pack()
{
    die_sound = NULL;
    hit_sound = NULL;
    score_sound = NULL;
    wing_sound = NULL;
}
#endif // DATA_H
