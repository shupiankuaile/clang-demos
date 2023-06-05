
#include <SDL2/SDL.h>
#include <stdio.h>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {

    SDL_Window* window = NULL;

    SDL_Surface* screen = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL_INIT_VIDEO SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }

    window = SDL_CreateWindow( "SDL hello world", 
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, 
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 
    SDL_WINDOW_SHOWN );
    if(window == NULL) {
        printf( "SDL_CreateWindow SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }


    screen = SDL_GetWindowSurface( window );
    if(screen == NULL) {
        printf( "SDL_GetWindowSurface SDL_Error: %s\n", SDL_GetError() );
    } else {

        SDL_Surface* image = NULL;
        image = SDL_LoadBMP("../../test_assets/test1/hello_world.bmp");
        SDL_BlitSurface(image, NULL, screen, NULL); // blit it to the screen
        SDL_FreeSurface(image);

        SDL_UpdateWindowSurface(window);

        SDL_Delay(2000);
    }


	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}