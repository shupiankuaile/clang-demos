
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "WRPG_sprite.h"

void WRPG_initSprite(WRPG_sprite* sprite, 
                    SDL_Renderer* renderer,
                    TTF_Font *gFont
                    ) {
    sprite->renderer = renderer;
    sprite->gFont = gFont;
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

void WRPG_loadSpriteFromText(WRPG_sprite* sprite, char* text, SDL_Color textColor) {

    SDL_Texture* texture = NULL;

    SDL_Surface* textSurface = TTF_RenderText_Solid( sprite->gFont, text, textColor );

    texture = SDL_CreateTextureFromSurface( sprite->renderer, textSurface );

    sprite->mTexture = texture;
    sprite->mWidth = textSurface->w;
    sprite->mHeight = textSurface->h;

    SDL_FreeSurface( textSurface );
}

void WRPG_setSpriteColorMod(WRPG_sprite* sprite, uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod( sprite->mTexture, r, g, b );
}

void WRPG_setSpriteAlphaMod(WRPG_sprite* sprite, uint8_t a) {
    SDL_SetTextureAlphaMod( sprite->mTexture, a );//调制纹理Alpha
}

void WRPG_setSpriteBlendMode(WRPG_sprite* sprite, SDL_BlendMode blending) {
    //设置混合功能
    SDL_SetTextureBlendMode( sprite->mTexture, blending );
}


void WRPG_renderSprite(WRPG_sprite* sprite, 
                int x, int y, 
                SDL_Rect* clip,
                double angle,
                SDL_Point* center,
                SDL_RendererFlip flip
                ) {

    SDL_Rect renderQuad = { x, y, sprite->mWidth, sprite->mHeight };//目标位置

    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( sprite->renderer, sprite->mTexture, clip, &renderQuad, angle, center, flip );
}

void WRPG_freeSprite(WRPG_sprite* sprite) {

    if( sprite->mTexture != NULL ) {
        SDL_DestroyTexture( sprite->mTexture );
        sprite->mTexture = NULL;
        sprite->mWidth = 0;
        sprite->mHeight = 0;
    }

}