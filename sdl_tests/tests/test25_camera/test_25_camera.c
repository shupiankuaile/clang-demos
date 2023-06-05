
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "WRPG_actor.h"

const int WORLD_WIDTH = 640*4;
const int WORLD_HEIGHT = 480*4;

const int CAMERA_WIDTH = 640;
const int CAMERA_HEIGHT = 480;

#define WRPG_TRUE 1
#define WRPG_FALSE 0

extern int DOT_WIDTH;
extern int DOT_HEIGHT;


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_Rect wallRect = { 0, 0, WORLD_WIDTH / 40, WORLD_HEIGHT / 40 };

SDL_Rect cameraRect = { 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };

#define WALKING_ANIMATION_FRAMES 3
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];

int WRPG_init();

void WRPG_close();

void WRPG_mainLoop();

int checkCollision( SDL_Rect a, SDL_Rect b );



int WRPG_init() {

    if(SDL_Init(SDL_INIT_VIDEO ) < 0) {
        printf( "SDL_INIT_VIDEO SDL_Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    gWindow = SDL_CreateWindow( "WRPG test25 camera", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            CAMERA_WIDTH, CAMERA_HEIGHT, SDL_WINDOW_SHOWN );
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

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );//初始化渲染器颜色
        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        WRPG_move(&actor, wallRect);


         //将相机对准演员的中心，计算出相机的世界坐标
        cameraRect.x = ( actor.mPosX + DOT_WIDTH / 2 ) - CAMERA_WIDTH / 2;
        cameraRect.y = ( actor.mPosY + DOT_HEIGHT / 2 ) - CAMERA_HEIGHT / 2;
        //摄像机要保持在世界范围内
        if( cameraRect.x < 0 ) { 
            cameraRect.x = 0;
        }
        if( cameraRect.y < 0 ) {
            cameraRect.y = 0;
        }
        if( cameraRect.x > WORLD_WIDTH - cameraRect.w ) {
            cameraRect.x = WORLD_WIDTH - cameraRect.w;
        }
        if( cameraRect.y > WORLD_HEIGHT - cameraRect.h ) {
            cameraRect.y = WORLD_HEIGHT - cameraRect.h;
        }


        //draw wall
        //随机生成一些墙，这些墙可能超出相机的范围
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );//绿色  
        for(int i=2; i<=11; i++) {
            wallRect.x = WORLD_WIDTH/i - cameraRect.x;
            wallRect.y = WORLD_HEIGHT/i - cameraRect.y;
            
            SDL_RenderFillRect( gRenderer, &wallRect );
        }


        SDL_Rect* currentClip = &gSpriteClips[ frame / 10 ];
        WRPG_renderActor(&actor, currentClip, &cameraRect);

        SDL_RenderPresent( gRenderer );//更新屏幕

        ++frame;
        //循环动画
        if( frame / 10 >= WALKING_ANIMATION_FRAMES ) {
            frame = 0;
        }

    }


    WRPG_freeActor(&actor);
}

int checkCollision( SDL_Rect a, SDL_Rect b ) {

    //矩形的边框
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //计算矩形A的边长
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //计算矩形B的边长
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
     //If any of the sides from A are outside of B
    if( bottomA <= topB ) {
        return WRPG_FALSE;
    }

    if( topA >= bottomB ) {
        return WRPG_FALSE;
    }

    if( rightA <= leftB ) {
        return WRPG_FALSE;
    }

    if( leftA >= rightB ) {
        return WRPG_FALSE;
    }

    //If none of the sides from A are outside B
    return WRPG_TRUE;

}

int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

