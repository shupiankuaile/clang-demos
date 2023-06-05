
#include "WRPG_miner.h"
#include "WRPG_MinerWife.h"
#include "WRPG_entityManager.h"
#include "WRPG_MessageDispatcher.h"
#include "WRPG_ConsoleUtils.h"

WRPG_EntityManager gEntityManager;

WRPG_MessageDispatcher gMessageDispatcher;

int main(int argc, char* argv[]) {

    WRPG_EM_init(&gEntityManager);
    WRPG_DM_init(&gMessageDispatcher);

    WRPG_miner* miner = WRPG_miner_init();
    WRPG_MinerWife* minerWife = WRPG_MinerWifeInit();

    for (int i=0; i<20; ++i) { 
        
        WRPG_miner_update(miner);

        printf(" Instant telegram dispatched at time: %lld \n", 
                        g_get_real_time()/1000
                        );

        if(i%2==0) {
            WRPG_DM_DispatchMessage(&gMessageDispatcher, 0, ent_Elsa, ent_Miner_Bob, Msg_HiHoneyImHome, NULL);
        } else {
            WRPG_DM_DispatchMessage(&gMessageDispatcher, 100, ent_Elsa, ent_Miner_Bob, Msg_StewReady, "1");
            WRPG_DM_DispatchMessage(&gMessageDispatcher, 100, ent_Elsa, ent_Miner_Bob, Msg_StewReady, "2");
            WRPG_DM_DispatchMessage(&gMessageDispatcher, 100, ent_Elsa, ent_Miner_Bob, Msg_StewReady, "3");
        }

        WRPG_DM_DispatchDelayedMessages(&gMessageDispatcher);

        Sleep(800);
    }


    WRPG_miner_free(miner);
    WRPG_MinerWifeFree(minerWife);
    WRPG_EM_Destroy(&gEntityManager);
    WRPG_DM_destroy(&gMessageDispatcher);

    //wait for a keypress before exiting
    WRPG_PressAnyKeyToContinue();

    return 0;
}
