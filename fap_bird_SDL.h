#ifndef SDL_H
#pragma once
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//some material use for rendering SDL declared here
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
//
//sdl2 load image function declared here
//this is a function created by LazyFoo

SDL_Texture* loadTexture( std::string path );
//
//
bool init_SDL( const std::string title, const int SCREEN_WIDTH, const int SCREEN_HEIGHT )
{
    bool success = true;
    window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        //Create renderer for window
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
        if( renderer == NULL )
        {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                success = false;
            }
        }
    }
    return success;
}
//
//
void close_SDL()
{
    //Free loaded image
    SDL_DestroyTexture( texture );
    texture = NULL;

    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
//
//
//
SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}
#endif // GALLERY_H

//
//
//


