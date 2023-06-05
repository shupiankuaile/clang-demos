
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "WRPG_sprite.h"

void WRPG_initSprite(WRPG_sprite* sprite, SDL_Renderer* renderer) {
    sprite->renderer = renderer;
}

void WRPG_loadSprite(WRPG_sprite* sprite, char* imagePath) {

    SDL_Texture* texture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(imagePath);

    //对图像进行颜色抠像
    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format,  0, 0xFF, 0xFF ) );

    texture = SDL_CreateTextureFromSurface( sprite->renderer, loadedSurface );

    sprite->mTexture = texture;
    sprite->mWidth = loadedSurface->w;
    sprite->mHeight = loadedSurface->h;

    SDL_FreeSurface( loadedSurface );

}

void WRPG_renderSprite(WRPG_sprite* sprite, int x, int y, SDL_Rect* clip) {

    SDL_Rect renderQuad = { x, y, sprite->mWidth, sprite->mHeight };//目标位置

    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy( sprite->renderer, sprite->mTexture, clip, &renderQuad );

}

void WRPG_freeSprite(WRPG_sprite* sprite) {

    if( sprite->mTexture != NULL ) {
        SDL_DestroyTexture( sprite->mTexture );
        sprite->mTexture = NULL;
        sprite->mWidth = 0;
        sprite->mHeight = 0;
    }

}