
#ifndef WRPG_MINER_WIFE_H
#define WRPG_MINER_WIFE_H

#include "WRPG_stateMachine.h"


typedef struct {

    int mEntityId;

    WRGP_stateMachine* mStateMachine;

} WRPG_MinerWife ;

WRPG_MinerWife* WRPG_MinerWifeInit();

void WRPG_MinerWifeFree(WRPG_MinerWife* minerWife);


#endif