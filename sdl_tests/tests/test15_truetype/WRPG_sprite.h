
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {

    SDL_Renderer* renderer;

    TTF_Font *gFont;

    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;

} WRPG_sprite ;

void WRPG_initSprite(WRPG_sprite* sprite, SDL_Renderer* renderer, TTF_Font *gFont);

void WRPG_loadSpriteFromText(WRPG_sprite* sprite, char* text, SDL_Color textColor);

void WRPG_loadSprite(WRPG_sprite* sprite, char* imagePath);

void WRPG_setSpriteColorMod(WRPG_sprite* sprite, uint8_t r, uint8_t g, uint8_t b);

void WRPG_setSpriteAlphaMod(WRPG_sprite* sprite, uint8_t a);

void WRPG_setSpriteBlendMode(WRPG_sprite* sprite, SDL_BlendMode blending);

void WRPG_renderSprite(WRPG_sprite* sprite, 
                int x, int y, 
                SDL_Rect* clip,
                double angle,
                SDL_Point* center,
                SDL_RendererFlip flip
                );

void WRPG_freeSprite(WRPG_sprite* sprite);