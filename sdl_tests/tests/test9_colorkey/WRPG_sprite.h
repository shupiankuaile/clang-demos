
#include <SDL2/SDL.h>

typedef struct {

    SDL_Renderer* renderer;

    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;

} WRPG_sprite ;

void WRPG_initSprite(WRPG_sprite* sprite, SDL_Renderer* renderer);

void WRPG_loadSprite(WRPG_sprite* sprite, char* imagePath);

void WRPG_renderSprite(WRPG_sprite* sprite, int x, int y);

void WRPG_freeSprite(WRPG_sprite* sprite);