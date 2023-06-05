

#include <stdio.h>
#include <SDL2/SDL.h>

enum keyPressSurfaceEnum {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* window = NULL;
SDL_Surface* screen = NULL;
int stop = 0;
SDL_Surface* keyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

SDL_Surface* loadImage(char* imagePath);

void loadSurfaces();

void mainLoop();




int main(int argc, char* args[]) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL_INIT_VIDEO SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }

    window = SDL_CreateWindow( "SDL stretch", 
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

        loadSurfaces();

        mainLoop();

    }


	SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}


SDL_Surface* loadImage(char* imagePath) {

    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* image = SDL_LoadBMP(imagePath);

    optimizedSurface = SDL_ConvertSurface( image, screen->format, 0 );//提前用屏幕格式优化图像

    SDL_FreeSurface( image );

    return optimizedSurface;
}

void loadSurfaces() {

    keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadImage("../../test_assets/test3/0.bmp");
    keyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadImage("../../test_assets/test3/1.bmp");
    keyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadImage("../../test_assets/test3/2.bmp");
    keyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadImage("../../test_assets/test3/3.bmp");
    keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadImage("../../test_assets/test3/4.bmp");

}

void mainLoop() {

    SDL_Event event;
    SDL_Surface* image = keyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            } else if (event.type == SDL_KEYDOWN) {
                
                if(event.key.keysym.sym == SDLK_UP) {
                    image = keyPressSurfaces[KEY_PRESS_SURFACE_UP];
                } else if(event.key.keysym.sym == SDLK_DOWN) {
                    image = keyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                } else if(event.key.keysym.sym == SDLK_LEFT) {
                    image = keyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                } else if(event.key.keysym.sym == SDLK_RIGHT) {
                    image = keyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                }
            }
        }

        SDL_BlitScaled(image, NULL, screen, &stretchRect);//拉伸至全屏幕

        SDL_UpdateWindowSurface(window);

    }

}