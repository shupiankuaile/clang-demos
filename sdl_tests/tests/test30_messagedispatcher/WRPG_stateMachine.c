
#include <stdio.h>
#include <malloc.h>

#include "WRPG_stateMachine.h"

WRGP_stateMachine* WRPG_SM_init(void* owner) {

    WRGP_stateMachine* sm = (WRGP_stateMachine*) malloc(sizeof(WRGP_stateMachine));

    sm->m_pOwner = owner;
    sm->m_pCurrentState = NULL;
    sm->m_pPreviousState = NULL;
    sm->m_pGlobalState = NULL;

    return sm;
}

void WRPG_SM_changeState(WRGP_stateMachine* sm, WRPG_state* state, void* entity) {

    sm->m_pCurrentState->exit(entity);
    
    sm->m_pPreviousState = sm->m_pCurrentState;
    sm->m_pCurrentState = state;

    sm->m_pCurrentState->enter(entity);

}


void WRPG_SM_update(WRGP_stateMachine* sm, void* entity) {

    if(sm->m_pGlobalState != NULL) {
        sm->m_pGlobalState->execute(entity);
    }

    if(sm->m_pCurrentState != NULL) {
        sm->m_pCurrentState->execute(entity);
    }

}


void WRPG_SM_setCurrState(WRGP_stateMachine* sm, WRPG_state* state) {

    sm->m_pCurrentState = state;

}

void WRPG_SM_setPrevState(WRGP_stateMachine* sm, WRPG_state* state) {

    sm->m_pPreviousState = state;

}

void WRPG_SM_setGlobalState(WRGP_stateMachine* sm, WRPG_state* state) {


    sm->m_pGlobalState = state;

}

void WRPG_SM_detroy(WRGP_stateMachine* sm) {

    WRPG_SM_freeState(sm->m_pCurrentState);
    WRPG_SM_freeState(sm->m_pPreviousState);
    WRPG_SM_freeState(sm->m_pGlobalState);

    free(sm);

}


WRPG_state* WRPG_SM_newState(int stateType) {

    WRPG_state* state = (WRPG_state*) malloc(sizeof(WRPG_state));

    state->m_iStateType = stateType;
    state->enter = NULL;
    state->execute = NULL;
    state->exit = NULL;

    return state;
}

void WRPG_SM_freeState(WRPG_state* state) {

    free(state);

}