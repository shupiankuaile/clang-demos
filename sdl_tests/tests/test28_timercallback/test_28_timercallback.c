#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "WRPG_sprite.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define WRPG_TRUE 1
#define WRPG_FALSE 0


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

int WRPG_init();

void WRPG_close();

void WRPG_mainLoop();

Uint32 callback( Uint32 interval, void* param )
{
	//Print callback message
	printf( "Callback called back with message: %s \n", (char*)param );

	return 0;
}


int WRPG_init() {

    if(SDL_Init(SDL_INIT_VIDEO ) < 0) {
        printf( "SDL_INIT_VIDEO SDL_Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    gWindow = SDL_CreateWindow( "WRPG test11 colormod", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    //开启垂直同步，帧率会限制为显示器的刷新频率--60FPS
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
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

    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return WRPG_FALSE;
    }

    gFont = TTF_OpenFont( "../../test_assets/test28/lazy.ttf", 28 );

    return WRPG_TRUE;
}

void WRPG_close() {


    if(gFont != NULL) {
        TTF_CloseFont( gFont );
    }
    if(gRenderer != NULL) {
        SDL_DestroyRenderer( gRenderer );
    }
    if(gWindow != NULL) {
        SDL_DestroyWindow( gWindow );
    }

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void WRPG_mainLoop() {

    int stop = 0;
    SDL_Event event;

    //Current time start time
    uint32_t startTime = 0;
    uint32_t countedFrames = 0;

    SDL_Color textColor = {0, 0, 0};

    WRPG_sprite promptSprite;
    WRPG_initSprite(&promptSprite, gRenderer, gFont);
    WRPG_loadSpriteFromText(&promptSprite, "Press ENTER to re time", textColor);

    WRPG_sprite timeFpsSprite;
    WRPG_initSprite(&timeFpsSprite, gRenderer, gFont);

    char timeFpsStr[1024] = { 0 };

    SDL_TimerID timerID = SDL_AddTimer( 3 * 1000, callback, "test 28 timer callback, wait 3 seconds!!" );

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            } else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {//Reset start time on return keypress
                startTime = SDL_GetTicks();
                countedFrames = 0;
            }
        }

        uint32_t elapseTime = SDL_GetTicks() - startTime;//从开始经过的毫秒数
        float avgFPS = 0.f;
        if(elapseTime == 0 ) {
            avgFPS = 0.f;
        } else {
            avgFPS = countedFrames / ( elapseTime / 1000.f );
        }

        sprintf(timeFpsStr, "Time: %d, FPS: %f", elapseTime, avgFPS);

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        WRPG_renderSprite(&promptSprite, 0, 0, NULL, 0, NULL, SDL_FLIP_NONE);

        WRPG_loadSpriteFromText(&timeFpsSprite, timeFpsStr, textColor);
        WRPG_renderSprite(&timeFpsSprite, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, NULL, 0, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent( gRenderer );//更新屏幕
        countedFrames++;//更新屏幕后，增加帧数，从开始经过的帧数
    }

    SDL_RemoveTimer( timerID );

    WRPG_freeSprite(&promptSprite);
}


int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

