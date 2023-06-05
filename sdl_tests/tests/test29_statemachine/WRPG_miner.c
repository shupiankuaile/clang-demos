
#include <stdio.h>
#include <malloc.h>

#include "WRPG_consts.h"
#include "WRPG_miner.h"
#include "WRPG_stateMachine.h"
#include "WRPG_ConsoleUtils.h"

//the amount of gold a miner must have before he feels comfortable
const int ComfortLevel       = 5;
//the amount of nuggets a miner can carry
const int MaxNuggets         = 3;
//above this value a miner is thirsty
const int ThirstLevel        = 5;
//above this value a miner is sleepy
const int TirednessThreshold = 5;

static WRPG_state* WRPG_miner_newState(WRPG_minerState minerState) {

    WRPG_state* state = WRPG_SM_newState(minerState);

    if(EnterMineAndDigForNugget == minerState) {
        state->enter = &WRPG_EnterMine_enter;
        state->execute = &WRPG_EnterMine_execute;
        state->exit = &WRPG_EnterMine_exit;

    } else if(VisitBankAndDepositGold == minerState) {
        state->enter = &WRPG_VisitBank_enter;
        state->execute = &WRPG_VisitBank_execute;
        state->exit = &WRPG_VisitBank_exit;

    } else if(GoHomeAndSleepTilRested == minerState) {
        state->enter = &WRPG_GoHome_enter;
        state->execute = &WRPG_GoHome_execute;
        state->exit = &WRPG_GoHome_exit;

    } else if(QuenchThirst == minerState) {
        state->enter = &WRPG_QuenchThirst_enter;
        state->execute = &WRPG_QuenchThirst_execute;
        state->exit = &WRPG_QuenchThirst_exit;
    }

    return state;

}

void WRPG_miner_update(WRPG_miner* miner) {

    WRPG_SetTextColor(FOREGROUND_RED| FOREGROUND_INTENSITY);

    miner->mThirst++;

    WRPG_SM_update(miner->mStateMachine, miner->mEntity);

}

void WRPG_miner_changeState(WRPG_miner* miner, WRPG_minerState minerState) {

    WRPG_state* state = WRPG_miner_newState(minerState);

    WRPG_SM_changeState(miner->mStateMachine, state, miner->mEntity);

}

void WRPG_miner_changeLocation(WRPG_miner* miner, WRPG_locationType location) {

    miner->mLocation = location;

}

WRPG_miner* WRPG_miner_init() {

    WRPG_miner* miner = (WRPG_miner*) malloc(sizeof(WRPG_miner));

    WRGP_stateMachine* stateMachine = WRPG_SM_init(miner);
    stateMachine->m_pCurrentState = WRPG_miner_newState(GoHomeAndSleepTilRested);

    WRPG_gameEntity* gameEntity = WRPG_EM_newEntity(1, "Tang");
    gameEntity->m_pEntity = miner;

    miner->mStateMachine = stateMachine;
    miner->mEntity = gameEntity;
    miner->mLocation = HOME;
    miner->mGoldCarried = 0;
    miner->mMoneyInBank = 0;
    miner->mThirst = 0;
    miner->mFatigue = 0;

    return miner;
}

void WRPG_miner_free(WRPG_miner* miner) {

    WRPG_SM_detroy(miner->mStateMachine);

    WRPG_EM_freeEntity(miner->mEntity);

    free(miner);
}


void WRPG_miner_addToGoldCarried(WRPG_miner* miner, int val) {
  miner->mGoldCarried += val;

  if (miner->mGoldCarried < 0) miner->mGoldCarried = 0;
}

void WRPG_miner_setGoldCarried(WRPG_miner* miner, int val) {
  miner->mGoldCarried = val;
}

void WRPG_miner_addToWealth(WRPG_miner* miner, int val) {
  miner->mMoneyInBank += val;

  if (miner->mMoneyInBank < 0) miner->mMoneyInBank = 0;
}

void WRPG_miner_increaseFatigue(WRPG_miner* miner) {
  miner->mFatigue++;
}

void WRPG_miner_decreaseFatigue(WRPG_miner* miner) {
  miner->mFatigue--;
}

int WRPG_miner_thirsty(WRPG_miner* miner) {
  if (miner->mThirst >= ThirstLevel){return WRPG_TRUE;}

  return WRPG_FALSE;
}


int WRPG_miner_fatigued(WRPG_miner* miner) {
  if (miner->mFatigue > TirednessThreshold) {
    return WRPG_TRUE;
  }

  return WRPG_FALSE;
}

int WRPG_miner_pocketsFull(WRPG_miner* miner) {
    
    if(miner->mGoldCarried >= MaxNuggets) {
        return WRPG_TRUE;
    }
    
    return WRPG_FALSE;
}

void WRPG_miner_buyAndDrinkAWhiskey(WRPG_miner* miner) { 
    miner->mThirst = 0;
    miner->mMoneyInBank -= 2;

}

////////////////////////////////////////////////////////////////////////////////
int WRPG_EnterMine_enter(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    if(miner->mLocation != GOLD_MINE) {
        
        printf("[%s] go mine \n", gameEntity->m_entityName);

        WRPG_miner_changeLocation(miner, GOLD_MINE);

    }

    return WRPG_TRUE;
}

int WRPG_EnterMine_execute(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    WRPG_miner_addToGoldCarried(miner, 1);

    WRPG_miner_increaseFatigue(miner);

    printf("[%s] dig a gold \n", gameEntity->m_entityName);

    if(WRPG_miner_pocketsFull(miner)) {
        WRPG_miner_changeState(miner, VisitBankAndDepositGold);
    }

    if(WRPG_miner_thirsty(miner)) {
        WRPG_miner_changeState(miner, QuenchThirst);
    }

    return WRPG_TRUE;
}

int WRPG_EnterMine_exit(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    printf("[%s] leaving mine \n", gameEntity->m_entityName);

    return WRPG_TRUE;

}

int WRPG_VisitBank_enter(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    if(miner->mLocation != BANK) {
        
        printf("[%s] go to bank \n", gameEntity->m_entityName);

        WRPG_miner_changeLocation(miner, BANK);

    }

    return WRPG_TRUE;
}

int WRPG_VisitBank_execute(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    //deposit the gold
    WRPG_miner_addToWealth(miner, miner->mGoldCarried);
    
    WRPG_miner_setGoldCarried(miner, 0);

    printf("[%s] total money: %d \n", gameEntity->m_entityName, miner->mMoneyInBank);

    //wealthy enough to have a well earned rest?
    if (miner->mMoneyInBank >= ComfortLevel) {
        printf("[%s] hohoho! enough money, go to sleep now \n", gameEntity->m_entityName);
        
        WRPG_miner_changeState(miner, GoHomeAndSleepTilRested);
    } else {//otherwise get more gold
        WRPG_miner_changeState(miner, EnterMineAndDigForNugget);
    }

    return WRPG_TRUE;
}

int WRPG_VisitBank_exit(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    printf("[%s] leaving the bank \n", gameEntity->m_entityName);

    return WRPG_TRUE;
}

int WRPG_GoHome_enter(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    if(miner->mLocation != HOME) {
        
        printf("[%s] going home \n", gameEntity->m_entityName);

        WRPG_miner_changeLocation(miner, HOME);

    }

    return WRPG_TRUE;
}

int WRPG_GoHome_execute(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    //if miner is not fatigued start to dig for nuggets again.
    if (!WRPG_miner_fatigued(miner)) {

        printf("[%s] wake up \n", gameEntity->m_entityName);

        WRPG_miner_changeState(miner, EnterMineAndDigForNugget);
        
    } else {
        //sleep
        printf("[%s] sleep ZZZ...  \n", gameEntity->m_entityName);

        WRPG_miner_decreaseFatigue(miner);

    } 

    return WRPG_TRUE;

}

int WRPG_GoHome_exit(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;

    printf("[%s] leaving home and go to work \n", gameEntity->m_entityName);

    return WRPG_TRUE;
}

int WRPG_QuenchThirst_enter(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    if(miner->mLocation != DRINK_BAR) {
        
        printf("[%s] walking to the bar \n", gameEntity->m_entityName);

        WRPG_miner_changeLocation(miner, DRINK_BAR);

    }

    return WRPG_TRUE;

}

int WRPG_QuenchThirst_execute(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    WRPG_miner* miner = (WRPG_miner*)gameEntity->m_pEntity;

    if (WRPG_miner_thirsty(miner)) {
     
        WRPG_miner_buyAndDrinkAWhiskey(miner);

        printf("[%s] drink very good, then go to work \n", gameEntity->m_entityName);

        WRPG_miner_changeState(miner, EnterMineAndDigForNugget);
    } else {
        printf("ERROR!\nERROR!\nERROR!\n");
    }  

    return WRPG_TRUE;
}

int WRPG_QuenchThirst_exit(void* entity) {

    WRPG_gameEntity* gameEntity = (WRPG_gameEntity*)entity;
    printf("[%s] Leaving the bar, feel good \n", gameEntity->m_entityName);

    return WRPG_TRUE;
}