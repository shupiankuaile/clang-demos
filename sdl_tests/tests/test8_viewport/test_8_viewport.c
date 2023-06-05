

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define WRPG_TRUE 1
#define WRPG_FALSE 0


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

int WRPG_init();

void WRPG_close();

SDL_Texture* WRPG_loadImage(char* imagePath);

void WRPG_mainLoop();



int WRPG_init() {

    gWindow = SDL_CreateWindow( "WRPG test8 viewport", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if(gRenderer == NULL) {
        printf( "Render could not be created! SDL Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );//初始化渲染器颜色


    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return WRPG_FALSE;
    }

    return WRPG_TRUE;
}

void WRPG_close() {

    if(gRenderer != NULL) {
        SDL_DestroyRenderer( gRenderer );
    }
    if(gWindow != NULL) {
        SDL_DestroyWindow( gWindow );
    }

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* WRPG_loadImage(char* imagePath) {

    SDL_Texture* texture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(imagePath);

    texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

    SDL_FreeSurface( loadedSurface );

    return texture;
}


void WRPG_mainLoop() {

    int stop = 0;
    SDL_Event event;

    SDL_Texture* tlTexture1 = WRPG_loadImage("../../test_assets/test8/top_left.png");
    SDL_Texture* trTexture1 = WRPG_loadImage("../../test_assets/test8/top_right.png");
    SDL_Texture* bmTexture1 = WRPG_loadImage("../../test_assets/test8/bottom.png");

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            }
        }

        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        SDL_Rect topLeftViewport = {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport( gRenderer, &topLeftViewport );
        SDL_RenderCopy( gRenderer, tlTexture1, NULL, NULL );

        SDL_Rect topRightViewport = {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport( gRenderer, &topRightViewport );
        SDL_RenderCopy( gRenderer, trTexture1, NULL, NULL );

        SDL_Rect bottomViewport = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport( gRenderer, &bottomViewport );
        SDL_RenderCopy( gRenderer, bmTexture1, NULL, NULL );

        SDL_RenderPresent( gRenderer );//更新屏幕

    }
}


int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

