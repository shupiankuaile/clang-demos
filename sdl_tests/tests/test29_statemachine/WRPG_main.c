
#include "WRPG_miner.h"
#include "WRPG_ConsoleUtils.h"

int main(int argc, char* argv[]) {


    WRPG_miner* miner = WRPG_miner_init();

    for (int i=0; i<20; ++i) { 
        
        WRPG_miner_update(miner);

        Sleep(800);
    }

    //wait for a keypress before exiting
    WRPG_PressAnyKeyToContinue();

    WRPG_miner_free(miner);

    return 0;
}
