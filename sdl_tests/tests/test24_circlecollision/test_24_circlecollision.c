
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

SDL_Rect wallRect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 10, SCREEN_HEIGHT / 10 };

SDL_Rect circleRect = { SCREEN_WIDTH / 5, SCREEN_HEIGHT / 5, SCREEN_WIDTH / 5, SCREEN_WIDTH / 5 };

#define WALKING_ANIMATION_FRAMES 3
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];

int WRPG_init();

void WRPG_close();

void WRPG_mainLoop();

int checkRectCollision( SDL_Rect a, SDL_Rect b );

int checkCircleCollision( WRPG_circle a, WRPG_circle b );

int checkCircleRectCollision( WRPG_circle a, SDL_Rect b );

double distanceSquared( int x1, int y1, int x2, int y2 );



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

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );//初始化渲染器颜色
        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        //draw wall
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );//绿色  
        SDL_RenderFillRect( gRenderer, &wallRect );

        //draw circle
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );//红色  
        SDL_RenderDrawRect( gRenderer, &circleRect );

        WRPG_circle circleCollider = {circleRect.x+circleRect.w/2, circleRect.y+circleRect.h/2, SCREEN_WIDTH / 10};

        WRPG_move(&actor, wallRect, circleCollider);

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

int checkRectCollision( SDL_Rect a, SDL_Rect b ) {

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


int checkCircleCollision( WRPG_circle a, WRPG_circle b ) {

    //计算总半径的平方
    int totalRadiusSquared = a.r + b.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    //如果圆心之间的距离小于它们的半径之和
    if( distanceSquared( a.x, a.y, b.x, b.y ) < ( totalRadiusSquared ) ) {
        //圆圈已经相撞
        return WRPG_TRUE;
    }

    //否则没有
    return WRPG_FALSE;

}

int checkCircleRectCollision( WRPG_circle a, SDL_Rect b ) {

    //碰撞框上的最近点
    int cX, cY;

    //寻找最近的X偏移量
    if( a.x < b.x ) {
        cX = b.x;
    } else if( a.x > b.x + b.w ) {
        cX = b.x + b.w;
    } else {
        cX = a.x;
    }
    //寻找最近的y偏移量
    if( a.y < b.y ) {
        cY = b.y;
    } else if( a.y > b.y + b.h ) {
        cY = b.y + b.h;
    } else {
        cY = a.y;
    }

    //如果最近的点在圆内
    if( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r )
    {
        //这个矩形框和圆圈相撞了
        return WRPG_TRUE;
    }

    //如果图形没有碰撞
    return WRPG_FALSE;

}


double distanceSquared( int x1, int y1, int x2, int y2 ){
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

