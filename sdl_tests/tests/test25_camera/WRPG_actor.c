#include <stdio.h>
#include <SDL2/SDL.h>
#include "WRPG_sprite.h"

#include "WRPG_actor.h"

extern int WORLD_WIDTH;
extern int WORLD_HEIGHT;

//点的尺寸
const int DOT_WIDTH = 32;
const int DOT_HEIGHT = 32;

//点的最大轴速
static const int DOT_VEL = 10;

int checkCollision( SDL_Rect a, SDL_Rect b );

void WRPG_initActor(WRPG_actor* actor, SDL_Renderer* renderer) {

    WRPG_sprite* actorSprite = (WRPG_sprite*)malloc(sizeof(WRPG_sprite)); 
    WRPG_initSprite(actorSprite, renderer);
    WRPG_loadSprite(actorSprite, "../../test_assets/test22/Actor3.png");

    actor->mSprite = actorSprite;
    actor->mPosX = 0;
    actor->mPosY = 0;
    actor->mVelX = 0;
    actor->mVelY = 0;

    actor->mCollider.x = 0;
    actor->mCollider.y = 0;
    actor->mCollider.w = DOT_WIDTH;
    actor->mCollider.h = DOT_HEIGHT;

}

void WRPG_handleEvent(WRPG_actor* actor, SDL_Event* e) {

    printf("repeat:%d, type:%d \n", e->key.repeat, e->type);

    //如果按了一个键
    if( e->type == SDL_KEYDOWN && e->key.repeat == 0 ) {
        //调整速度
        switch( e->key.keysym.sym )
        {
            case SDLK_UP: actor->mVelY -= DOT_VEL; break;
            case SDLK_DOWN: actor->mVelY += DOT_VEL; break;
            case SDLK_LEFT: actor->mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: actor->mVelX += DOT_VEL; break;
        }
    } else if( e->type == SDL_KEYUP && e->key.repeat == 0 ) {//如果有按键被释放
        //调整速度
        switch( e->key.keysym.sym )
        {
            case SDLK_UP: actor->mVelY += DOT_VEL; break;
            case SDLK_DOWN: actor->mVelY -= DOT_VEL; break;
            case SDLK_LEFT: actor->mVelX += DOT_VEL; break;
            case SDLK_RIGHT: actor->mVelX -= DOT_VEL; break;
        }
    }

}

void WRPG_move(WRPG_actor* actor, SDL_Rect wallCollider) {

    //向左或向右移动点
    actor->mPosX += actor->mVelX;
    actor->mCollider.x = actor->mPosX;

    //如果点向左或向右走得太远的话
    if( ( actor->mPosX < 0 ) 
            || ( actor->mPosX + DOT_WIDTH > WORLD_WIDTH )
            || (checkCollision(actor->mCollider, wallCollider)) ) {
        //退回
        actor->mPosX -= actor->mVelX;
        actor->mCollider.x = actor->mPosX;
    }

     //向上或向下移动点
    actor->mPosY += actor->mVelY;
    actor->mCollider.y = actor->mPosY;

    //如果点向上或向下走得太远
    if( ( actor->mPosY < 0 ) 
            || ( actor->mPosY + DOT_HEIGHT > WORLD_HEIGHT )
            || (checkCollision(actor->mCollider, wallCollider)) ) {
        //退回
        actor->mPosY -= actor->mVelY;
        actor->mCollider.y = actor->mPosY;
    }

}

void WRPG_renderActor(WRPG_actor* actor, SDL_Rect* clip, SDL_Rect* camera) {

    //用点的世界坐标和相机的世界坐标，计算出点在相机坐标系的位置
    WRPG_renderSprite(actor->mSprite, 
                        actor->mPosX - camera->x, 
                        actor->mPosY - camera->y, 
                        clip);

}

void WRPG_freeActor(WRPG_actor* actor) {

    WRPG_freeSprite(actor->mSprite);
    free(actor->mSprite);

}
