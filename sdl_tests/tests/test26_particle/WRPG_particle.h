
#include <SDL2/SDL.h>
#include "WRPG_sprite.h"

#ifndef WRPG_PARTICLE_h
#define WRPG_PARTICLE_h


typedef struct {

    WRPG_sprite* mSprite;

    WRPG_sprite* mShimmerSprite;

    int mPosX;
    int mPosY;

    int mFrame;

} WRPG_particle ;

WRPG_particle* WRPG_initParticle(SDL_Renderer* renderer, int x, int y);

int WRPG_isDead(WRPG_particle* particle);

void WRPG_renderParticle(WRPG_particle* particle);

void WRPG_freeParticle(WRPG_particle* particle);

#endif