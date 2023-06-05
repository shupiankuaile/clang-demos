#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define WRPG_TRUE 1
#define WRPG_FALSE 0


SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

//要播放的音乐
Mix_Music *gMusic = NULL;

//将要使用的音效
Mix_Chunk *gScratch = NULL;

int WRPG_init();

void WRPG_close();

void WRPG_mainLoop();


int WRPG_init() {

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO  ) < 0) {
        printf( "SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER SDL_Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    gWindow = SDL_CreateWindow( "WRPG test11 colormod", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if(gRenderer == NULL) {
        printf( "Render could not be created! SDL Error: %s\n", SDL_GetError() );
        return WRPG_FALSE;
    }

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );//初始化渲染器颜色


    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return WRPG_FALSE;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return WRPG_FALSE;
    }

    //加载音乐
    gMusic = Mix_LoadMUS( "../../test_assets/test19/Porkkana.mp3" );
    if( gMusic == NULL ) {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
        return WRPG_FALSE;
    }
    
    //加载音效
    gScratch = Mix_LoadWAV( "../../test_assets/test19/beat.wav" );
    if( gScratch == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        return WRPG_FALSE;
    }

    return WRPG_TRUE;
}

void WRPG_close() {

    if(gScratch != NULL) {
        Mix_FreeChunk( gScratch );
    }

    if(gMusic != NULL) {
        Mix_FreeMusic( gMusic );
    }

    if(gRenderer != NULL) {
        SDL_DestroyRenderer( gRenderer );
    }
    if(gWindow != NULL) {
        SDL_DestroyWindow( gWindow );
    }

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


void WRPG_mainLoop() {

    int stop = 0;
    SDL_Event e;

    while(!stop) {

        while( SDL_PollEvent( &e ) != 0 ) {

            if( e.type == SDL_QUIT ) {
                stop = 1;
            } else if(e.type == SDL_KEYDOWN) {
                switch( e.key.keysym.sym ) {
                    case SDLK_1:
                        Mix_PlayChannel( -1, gScratch, 0 );
                        break;
                    
                    case SDLK_2:
                        //如果没有音乐播放
                        if( Mix_PlayingMusic() == 0 ) {
                            //播放音乐
                            Mix_PlayMusic( gMusic, -1 );
                        } else {//如果正在播放音乐
                            //如果音乐被暂停
                            if( Mix_PausedMusic() == 1 ) {
                                //Resume the music
                                Mix_ResumeMusic();
                            }  else {//如果正在播放音乐
                                //暂停音乐
                                Mix_PauseMusic();
                            }
                        }
                        break;
                    
                    case SDLK_0:
                        //停止音乐
                        Mix_HaltMusic();
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        SDL_RenderPresent( gRenderer );//更新屏幕

    }

}


int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

