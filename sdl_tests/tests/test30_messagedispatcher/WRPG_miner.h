

#ifndef WRPG_MINER_H
#define WRPG_MINER_H

#include "WRPG_stateMachine.h"
#include "WRPG_entityManager.h"
#include "WRPG_MessageDispatcher.h"

typedef enum {

    GOLD_MINE,

    BANK,

    HOME,

    DRINK_BAR

} WRPG_locationType;

typedef enum {

    EnterMineAndDigForNugget,

    VisitBankAndDepositGold,

    GoHomeAndSleepTilRested,

    QuenchThirst

} WRPG_minerState ;

typedef struct {

    int mEntityId;

    WRGP_stateMachine* mStateMachine;

    WRPG_locationType mLocation;

    int mGoldCarried;

    int mMoneyInBank;

    int mThirst;

    int mFatigue;


} WRPG_miner ;

WRPG_miner* WRPG_miner_init();

void WRPG_miner_update(WRPG_miner* miner);

void WRPG_miner_changeState(WRPG_miner* miner, WRPG_minerState state);

void WRPG_miner_handleMessage(void* entity, WRPG_Message* message);

void WRPG_miner_free(WRPG_miner* miner);


void WRPG_miner_changeLocation(WRPG_miner* miner, WRPG_locationType location);

//////////////////////////////////////////////////////////////////////////////////
int WRPG_EnterMine_enter(void* entity);

int WRPG_EnterMine_execute(void* entity);

int WRPG_EnterMine_exit(void* entity);

int WRPG_VisitBank_enter(void* entity);

int WRPG_VisitBank_execute(void* entity);

int WRPG_VisitBank_exit(void* entity);

int WRPG_GoHome_enter(void* entity);

int WRPG_GoHome_execute(void* entity);

int WRPG_GoHome_exit(void* entity);

int WRPG_QuenchThirst_enter(void* entity);

int WRPG_QuenchThirst_execute(void* entity);

int WRPG_QuenchThirst_exit(void* entity);


#endif