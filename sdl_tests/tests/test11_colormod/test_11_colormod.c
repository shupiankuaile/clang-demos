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

    WRPG_sprite colorSprite;

    WRPG_initSprite(&colorSprite, gRenderer);
    WRPG_loadSprite(&colorSprite, "../../test_assets/test11/colormod.png");

    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            } else if( event.type == SDL_KEYDOWN ) {
                printf("SDL_KEYDOWN, keysym=%d", event.key.keysym.sym);

                switch( event.key.keysym.sym ) {
                        //增加红色
                    case SDLK_q:
                        r += 32;
                        break;

                        //增加绿色
                    case SDLK_w:
                        g += 32;
                        break;

                        //增加蓝色
                    case SDLK_e:
                        b += 32;
                        break;

                        //减少红色
                    case SDLK_a:
                        r -= 32;
                        break;

                        //减少绿色
                    case SDLK_s:
                        g -= 32;
                        break;

                        //减少蓝色
                    case SDLK_d:
                        b -= 32;
                        break;
                }
            }
        }

        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        WRPG_setSpriteColorMod(&colorSprite, r, g, b);
        WRPG_renderSprite(&colorSprite, 0, 0, NULL);

        SDL_RenderPresent( gRenderer );//更新屏幕

    }


    WRPG_freeSprite(&colorSprite);
}


int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

