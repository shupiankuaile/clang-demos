
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "WRPG_actor.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define WRPG_TRUE 1
#define WRPG_FALSE 0


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

#define WALKING_ANIMATION_FRAMES 3
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];

int WRPG_init();

void WRPG_close();

void WRPG_mainLoop();


int WRPG_init() {

    if(SDL_Init(SDL_INIT_VIDEO ) < 0) {
        printf( "SDL_INIT_VIDEO SDL_Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    gWindow = SDL_CreateWindow( "WRPG test22 move", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );//垂直同步
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


    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w =  32;
    gSpriteClips[ 0 ].h =  32;

    gSpriteClips[ 1 ].x =  32;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w =  32;
    gSpriteClips[ 1 ].h =  32;
    
    gSpriteClips[ 2 ].x =  64;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w =  32;
    gSpriteClips[ 2 ].h =  32;


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


void WRPG_mainLoop() {

    int stop = 0;
    SDL_Event event;

    int frame = 0;

    WRPG_actor actor;
    WRPG_initActor(&actor, gRenderer);

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            } else {
                WRPG_handleEvent(&actor, &event);
            }
        }

        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        WRPG_move(&actor);

        SDL_Rect* currentClip = &gSpriteClips[ frame / 10 ];
        WRPG_renderActor(&actor, currentClip);

        SDL_RenderPresent( gRenderer );//更新屏幕

        ++frame;
        //循环动画
        if( frame / 10 >= WALKING_ANIMATION_FRAMES ) {
            frame = 0;
        }

    }


    WRPG_freeActor(&actor);
}


int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

