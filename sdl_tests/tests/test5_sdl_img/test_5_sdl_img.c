

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

int init();

SDL_Surface* loadImage(char* imagePath);

void mainLoop();

int main(int argc, char* args[]) {

    if(init()) {
        mainLoop();
    }


    if(!window) {
        SDL_DestroyWindow(window);
    }
	SDL_Quit();
    return 0;
}

int init() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL_INIT_VIDEO SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }

    window = SDL_CreateWindow( "SDL img", 
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, 
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 
    SDL_WINDOW_SHOWN );
    if(window == NULL) {
        printf( "SDL_CreateWindow SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }

    screen = SDL_GetWindowSurface( window );
    if(screen == NULL) {
        printf( "SDL_GetWindowSurface SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }

    //初始化PNG加载
    int imgFlags = IMG_INIT_PNG;//数字2
    if( !( IMG_Init( imgFlags ) & imgFlags ) )//IMG_Init返回初始化成功的flags
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 0;
    }

    return 1;
}

SDL_Surface* loadImage(char* imagePath) {

    SDL_Surface* optimizedSurface = NULL;

    SDL_Surface* image = IMG_Load(imagePath);

    optimizedSurface = SDL_ConvertSurface( image, screen->format, 0 );//提前用屏幕格式优化图像

    SDL_FreeSurface( image );

    return optimizedSurface;

}

void mainLoop() {

    int stop = 0;
    SDL_Event event;

    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = SCREEN_WIDTH;
    stretchRect.h = SCREEN_HEIGHT;

    SDL_Surface* image = loadImage("../../test_assets/test5/image.png");
    
    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            }
        }

        SDL_BlitScaled(image, NULL, screen, &stretchRect);//拉伸至全屏幕

        SDL_UpdateWindowSurface(window);

    }


}