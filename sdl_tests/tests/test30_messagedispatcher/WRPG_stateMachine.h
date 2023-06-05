

#ifndef WRPG_STATE_MACHINE_H
#define WRPG_STATE_MACHINE_H

#include <stdio.h>

typedef struct {

    int m_iStateType;

    int (*enter)(void* entity);

    int (*execute)(void* entity);

    int (*exit)(void* entity);

} WRPG_state ;

typedef struct {

    void*         m_pOwner;

    WRPG_state*   m_pCurrentState;
  
    WRPG_state*   m_pPreviousState;

    WRPG_state*   m_pGlobalState;

} WRGP_stateMachine;

WRGP_stateMachine* WRPG_SM_init(void* owner);

void WRPG_SM_changeState(WRGP_stateMachine* stateMachine, WRPG_state* state, void* entity);

void WRPG_SM_update(WRGP_stateMachine* stateMachine, void* entity);

void WRPG_SM_setCurrState(WRGP_stateMachine* stateMachine, WRPG_state* state);

void WRPG_SM_setPrevState(WRGP_stateMachine* stateMachine, WRPG_state* state);

void WRPG_SM_setGlobalState(WRGP_stateMachine* stateMachine, WRPG_state* state);

void WRPG_SM_detroy(WRGP_stateMachine* stateMachine);


WRPG_state* WRPG_SM_newState(int stateType);

void WRPG_SM_freeState(WRPG_state* state);

#endif