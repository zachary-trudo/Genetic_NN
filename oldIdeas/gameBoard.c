#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

void buildGameBoard(SDL_Window *window, SDL_Surface *screenSurface)
{
    SDL_Window *window = NULL;

    SDL_Surface * screenSurface = NULL;

    if ( SDL_Init( SDL_INIT_VIDEO) < 0 )
    {
        printf("SDL could not init: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow( "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created SDL_ERROR: %s\n", SDL_GetError() );
        }
        else
        {
            screenSurface = SDL_GetWindowSurface( window);

            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface( window);

            SDL_Delay(2000);
        }
    }

    SDL_DestroyWindow( window);

    SDL_Quit();

    return 0;
}





