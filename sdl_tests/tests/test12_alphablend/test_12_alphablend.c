#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "WRPG_sprite.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define WRPG_TRUE 1
#define WRPG_FALSE 0


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

int WRPG_init();

void WRPG_close();

void WRPG_mainLoop();


int WRPG_init() {

    gWindow = SDL_CreateWindow( "WRPG test11 colormod", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
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


void WRPG_mainLoop() {

    int stop = 0;
    SDL_Event event;

    WRPG_sprite blendSprite;

    WRPG_initSprite(&blendSprite, gRenderer);
    WRPG_loadSprite(&blendSprite, "../../test_assets/test12/alphablend.png");
    WRPG_setSpriteBlendMode(&blendSprite, SDL_BLENDMODE_BLEND);

    uint8_t a = 255;

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            } else if( event.type == SDL_KEYDOWN ) {
                printf("SDL_KEYDOWN, keysym=%d", event.key.keysym.sym);

                switch( event.key.keysym.sym ) {
                    case SDLK_UP:
                        a += 32;
                        break;

                    case SDLK_DOWN:
                        a += 32;
                        break;
                }
            }
        }

        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        if(a > 255) {
            a = 255;
        } else if(a < 0) {
            a = 0;
        }
        WRPG_setSpriteAlphaMod(&blendSprite, a);
        WRPG_renderSprite(&blendSprite, 0, 0, NULL);

        SDL_RenderPresent( gRenderer );//更新屏幕

    }


    WRPG_freeSprite(&blendSprite);
}


int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

