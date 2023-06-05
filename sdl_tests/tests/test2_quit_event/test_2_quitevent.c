
#include <stdio.h>

#include <SDL2/SDL.h>




const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



int main(int argc, char* args[]) {

    SDL_Window* window = NULL;
    SDL_Surface* screen = NULL;
    int stop = 0;
    SDL_Event event;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL_INIT_VIDEO SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }

    window = SDL_CreateWindow( "SDL quit event", 
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

        while(!stop) {

            while( SDL_PollEvent( &event ) != 0 ) {

                if( event.type == SDL_QUIT ) {
                    stop = 1;
                }
            }

            SDL_FillRect(screen, NULL, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(window);

        }

    }


	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}