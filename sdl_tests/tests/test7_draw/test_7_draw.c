
#include <stdio.h>
#include <SDL2/SDL.h>

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

    gWindow = SDL_CreateWindow( "WRPG test7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
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

    return WRPG_TRUE;
}

void WRPG_close() {

    if(gRenderer != NULL) {
        SDL_DestroyRenderer( gRenderer );
    }
    if(gWindow != NULL) {
        SDL_DestroyWindow( gWindow );
    }

    SDL_Quit();
}



void WRPG_mainLoop() {

    int stop = 0;
    SDL_Event event;

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );//设置背景颜色
        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        //渲染红色填充四边形
        SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );        
        SDL_RenderFillRect( gRenderer, &fillRect );

        //渲染绿色轮廓的四边形
        SDL_Rect outlineRect = { SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );        
        SDL_RenderDrawRect( gRenderer, &outlineRect );

        //画蓝色横线
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );        
        SDL_RenderDrawLine( gRenderer, SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, SCREEN_WIDTH, SCREEN_HEIGHT );

        //画出黄点的垂直线
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        for( int i = 0; i < 20; i++ ) {
            SDL_RenderDrawPoint( gRenderer, (SCREEN_WIDTH/2)+(i*SCREEN_WIDTH/100), SCREEN_HEIGHT/2 );
        }

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

