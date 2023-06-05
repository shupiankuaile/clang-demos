
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "WRPG_sprite.h"
#include "WRPG_particle.h"

#define WRPG_PARTICLE_ALIVE_FRAME 10


WRPG_particle* WRPG_initParticle(SDL_Renderer* renderer, int x, int y) {

    WRPG_particle* particle = (WRPG_particle*)malloc(sizeof(WRPG_particle)); 

    WRPG_sprite* shimmerSprite = (WRPG_sprite*)malloc(sizeof(WRPG_sprite)); 
    WRPG_initSprite(shimmerSprite, renderer);
    WRPG_loadSprite(shimmerSprite, "../../test_assets/test26/shimmer.bmp");

    particle->mShimmerSprite = shimmerSprite;


    WRPG_sprite* sprite = (WRPG_sprite*)malloc(sizeof(WRPG_sprite)); 
    WRPG_initSprite(sprite, renderer);
    
    switch( rand() % 3 ) {
        case 0: WRPG_loadSprite(sprite, "../../test_assets/test26/blue.bmp"); break;
        case 1: WRPG_loadSprite(sprite, "../../test_assets/test26/green.bmp"); break;
        case 2: WRPG_loadSprite(sprite, "../../test_assets/test26/red.bmp"); break;
    }

    particle->mSprite = sprite;

    particle->mFrame = rand() % 5;

    particle->mPosX = x - 5 + ( rand() % 25 );
    particle->mPosY = y - 5 + ( rand() % 25 );

    return particle;
}

int WRPG_isDead(WRPG_particle* particle) {

    if(particle->mFrame > WRPG_PARTICLE_ALIVE_FRAME) {
        return 1;
    }

    return 0;

}

void WRPG_renderParticle(WRPG_particle* particle) {

    WRPG_renderSprite(particle->mSprite, particle->mPosX, particle->mPosY, NULL);

    if( particle->mFrame % 2 == 0 )
    {
        WRPG_renderSprite(particle->mShimmerSprite, particle->mPosX, particle->mPosY, NULL);
    }

    particle->mFrame++;
}

void WRPG_freeParticle(WRPG_particle* particle) {

    WRPG_freeSprite(particle->mSprite);
    free(particle->mSprite);

    WRPG_freeSprite(particle->mShimmerSprite);
    free(particle->mShimmerSprite);

    free(particle);
}

