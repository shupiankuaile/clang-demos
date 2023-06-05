
#include <SDL2/SDL.h>

#include "WRPG_sprite.h"

#ifndef WRPG_BUTTON_H
#define WRPG_BUTTON_H

typedef enum {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
} ButtonSprite;


typedef struct {

    SDL_Point mPosition;

    WRPG_sprite* mSprite;

    ButtonSprite mCurrentSprite;

} WRPG_button ;


void WRPG_initBtn(WRPG_button* button, WRPG_sprite* sprite, SDL_Point position);

void WRPG_handleEvent(WRPG_button* button, SDL_Event* event);

void WRPG_renderBtn(WRPG_button* button);

void WRPG_freeBtn(WRPG_button* button);

#endif