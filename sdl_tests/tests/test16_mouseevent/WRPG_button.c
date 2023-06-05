
#include <SDL2/SDL.h>

#include "WRPG_sprite.h"
#include "WRPG_button.h"

//按钮常量
const int BUTTON_WIDTH = 160;
const int BUTTON_HEIGHT = 120;

#define TOTAL_SPRITE_NUM 4
SDL_Rect gSpriteClips[ TOTAL_SPRITE_NUM ];

void WRPG_initBtn(WRPG_button* button, WRPG_sprite* sprite, SDL_Point position) {
    button->mSprite = sprite;
    button->mPosition = position;

    gSpriteClips[BUTTON_SPRITE_MOUSE_OVER_MOTION].x = 0;
    gSpriteClips[BUTTON_SPRITE_MOUSE_OVER_MOTION].y = 0;
    gSpriteClips[BUTTON_SPRITE_MOUSE_OVER_MOTION].w = BUTTON_WIDTH;
    gSpriteClips[BUTTON_SPRITE_MOUSE_OVER_MOTION].h = BUTTON_HEIGHT;

    gSpriteClips[BUTTON_SPRITE_MOUSE_OUT].x = BUTTON_WIDTH;
    gSpriteClips[BUTTON_SPRITE_MOUSE_OUT].y = 0;
    gSpriteClips[BUTTON_SPRITE_MOUSE_OUT].w = BUTTON_WIDTH;
    gSpriteClips[BUTTON_SPRITE_MOUSE_OUT].h = BUTTON_HEIGHT;

    gSpriteClips[BUTTON_SPRITE_MOUSE_UP].x = 0;
    gSpriteClips[BUTTON_SPRITE_MOUSE_UP].y = BUTTON_HEIGHT;
    gSpriteClips[BUTTON_SPRITE_MOUSE_UP].w = BUTTON_WIDTH;
    gSpriteClips[BUTTON_SPRITE_MOUSE_UP].h = BUTTON_HEIGHT;

    gSpriteClips[BUTTON_SPRITE_MOUSE_DOWN].x = BUTTON_WIDTH;
    gSpriteClips[BUTTON_SPRITE_MOUSE_DOWN].y = BUTTON_HEIGHT;
    gSpriteClips[BUTTON_SPRITE_MOUSE_DOWN].w = BUTTON_WIDTH;
    gSpriteClips[BUTTON_SPRITE_MOUSE_DOWN].h = BUTTON_HEIGHT;
    
}

void WRPG_handleEvent(WRPG_button* button, SDL_Event* e) {

     if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ) {
        //获取鼠标位置
        int x, y;
        SDL_GetMouseState( &x, &y );

        //检查鼠标是否在按钮上
        int inside = 1;
        //鼠标在按钮左边
        if( x < button->mPosition.x ) {
            inside = 0;
        } else if( x > button->mPosition.x + BUTTON_WIDTH ) {//鼠标在按钮的右边
            inside = 0;
        } else if( y < button->mPosition.y ) {//鼠标在按钮上方
            inside = 0;
        } else if( y > button->mPosition.y + BUTTON_HEIGHT ) {//鼠标在按钮下方
            inside = 0;
        }

        //鼠标在按钮外
        if( !inside ) {
            button->mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        } else {//鼠标在按钮内
            //Set mouse over sprite
            switch( e->type ) {
                case SDL_MOUSEMOTION:
                button->mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            
                case SDL_MOUSEBUTTONDOWN:
                button->mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
                
                case SDL_MOUSEBUTTONUP:
                button->mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }

}

void WRPG_renderBtn(WRPG_button* button) {

    WRPG_renderSprite(button->mSprite, 
                button->mPosition.x, button->mPosition.y, 
                &gSpriteClips[button->mCurrentSprite],
                0,
                NULL,
                SDL_FLIP_NONE);

}

void WRPG_freeBtn(WRPG_button* button) {
    if(button->mSprite != NULL) {
        WRPG_freeSprite(button->mSprite);
    }
}