
#include <stdio.h>
#include "WRPG_MinerWife.h"
#include "WRPG_stateMachine.h"
#include "WRPG_entityManager.h"

extern WRPG_EntityManager gEntityManager;

WRPG_MinerWife* WRPG_MinerWifeInit() {

    WRPG_MinerWife* minerWife = (WRPG_MinerWife*) malloc(sizeof(WRPG_MinerWife));

    WRPG_gameEntity* gameEntity = WRPG_EM_newEntity(ent_Elsa, WRPG_GetNameOfEntity(ent_Elsa));
    gameEntity->m_pEntity = minerWife;
    gameEntity->handleMessage = NULL;
    WRPG_EM_RegisterEntity(&gEntityManager, gameEntity);



    minerWife->mStateMachine = NULL;
    minerWife->mEntityId = ent_Elsa;

    return minerWife;

}

void WRPG_MinerWifeFree(WRPG_MinerWife* minerWife) {

    if(minerWife->mStateMachine != NULL) {
        WRPG_SM_detroy(minerWife->mStateMachine);
    }

    free(minerWife);

}