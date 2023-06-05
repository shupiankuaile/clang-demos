
#include <SDL2/SDL.h>
#include "WRPG_sprite.h"

#ifndef WRPG_ACTOR_H
#define WRPG_ACTOR_H

typedef struct {

    WRPG_sprite* mSprite;

    int mPosX;
    int mPosY;

    //轴向速度
    int mVelX;
    int mVelY;

    //碰撞框
    SDL_Rect mCollider;

} WRPG_actor ;

void WRPG_initActor(WRPG_actor* actor, SDL_Renderer* renderer);

void WRPG_handleEvent(WRPG_actor* actor, SDL_Event* event);

void WRPG_move(WRPG_actor* actor, SDL_Rect wallCollider);

void WRPG_renderActor(WRPG_actor* actor, SDL_Rect* clip);

void WRPG_freeActor(WRPG_actor* actor);

#endif