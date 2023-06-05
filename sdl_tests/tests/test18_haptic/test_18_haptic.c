
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "WRPG_sprite.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#define WRPG_TRUE 1
#define WRPG_FALSE 0

#define WRPG_JOYSTICK_INSTANCE_ID 0

//模拟手柄死区
const int JOYSTICK_DEAD_ZONE = 8000;

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

SDL_GameController *gGameController = NULL;

SDL_Haptic* gControllerHaptic = NULL;

int WRPG_init();

void WRPG_close();

void WRPG_mainLoop();


int WRPG_init() {

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC ) < 0) {
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

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    //检查操纵杆
    if( SDL_NumJoysticks() < 1 ) {
        printf( "Warning: No joysticks connected!\n" );
    } else {

        if(!SDL_IsGameController(WRPG_JOYSTICK_INSTANCE_ID)) {
            printf( "Warning: No GameController connected!\n" );
            return WRPG_FALSE;
        }

        //加载操纵杆
        gGameController = SDL_GameControllerOpen( WRPG_JOYSTICK_INSTANCE_ID );
        if( gGameController == NULL ) {
            printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            return WRPG_FALSE;
        }
    }

    //Get controller haptic device
    SDL_Joystick* joystick = SDL_GameControllerGetJoystick(gGameController);
    gControllerHaptic = SDL_HapticOpenFromJoystick( joystick );
    if( gControllerHaptic == NULL ) {
        printf( "Warning: Controller does not support haptics! SDL Error: %s\n", SDL_GetError() );
    } else {
        //Get initialize rumble
        if( SDL_HapticRumbleInit( gControllerHaptic ) < 0 ) {
            printf( "Warning: Unable to initialize rumble! SDL Error: %s\n", SDL_GetError() );
        }
    }

    return WRPG_TRUE;
}

void WRPG_close() {

    if(gControllerHaptic != NULL) {
        SDL_HapticClose( gControllerHaptic );
    }
    if(gGameController != NULL) {
        SDL_GameControllerClose( gGameController );
    }
    if(gRenderer != NULL) {
        SDL_DestroyRenderer( gRenderer );
    }
    if(gWindow != NULL) {
        SDL_DestroyWindow( gWindow );
    }

    IMG_Quit();
    SDL_Quit();
}


void WRPG_mainLoop() {

    int stop = 0;
    SDL_Event event;

    //正常化方向
    int xDir = 0;
    int yDir = 0;

    WRPG_sprite arrowSprite;

    WRPG_initSprite(&arrowSprite, gRenderer, NULL);
    WRPG_loadSprite(&arrowSprite, "../../test_assets/test17/arrow.png");

    while(!stop) {

        while( SDL_PollEvent( &event ) != 0 ) {

            if( event.type == SDL_QUIT ) {
                stop = 1;
            } else if (event.type == SDL_CONTROLLERAXISMOTION) {
                if(event.caxis.which == WRPG_JOYSTICK_INSTANCE_ID) {
                    //X axis motion
                    if( event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX ) {//左侧X轴
                        if( event.caxis.value < -JOYSTICK_DEAD_ZONE ) {//死区左侧
                            xDir = -1;
                        } else if( event.caxis.value > JOYSTICK_DEAD_ZONE ) {//死区右侧
                            xDir =  1;
                        } else {
                            xDir = 0;
                        }
                    } else if( event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTY ) {//左侧Y轴
                        if( event.caxis.value < -JOYSTICK_DEAD_ZONE ) { //死区下方
                            yDir = -1;
                        } else if( event.caxis.value > JOYSTICK_DEAD_ZONE ) {//死区上方
                            yDir =  1;
                        } else {
                            yDir = 0;
                        }
                    }

                }
            } else if(event.type == SDL_CONTROLLERBUTTONDOWN) {
                //以75%的强度播放隆隆声，持续500毫秒。
                if( SDL_HapticRumblePlay( gControllerHaptic, 0.75, 500 ) != 0 ) {
                    printf( "Warning: Unable to play rumble! %s\n", SDL_GetError() );
                }
            }
        }

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );//清空屏幕，使用设置的颜色

        //Calculate angle
        double joystickAngle = atan2( (double)yDir, (double)xDir ) * ( 180.0 / M_PI );

        //Correct angle
        if( xDir == 0 && yDir == 0 ) {
            joystickAngle = 0;
        }

        WRPG_renderSprite(&arrowSprite, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, NULL, joystickAngle, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent( gRenderer );//更新屏幕

    }


    WRPG_freeSprite(&arrowSprite);
}


int main(int argc, char* args[]) {

    if(WRPG_init()) {
        WRPG_mainLoop();
    }

    WRPG_close();
    return 0;
}

