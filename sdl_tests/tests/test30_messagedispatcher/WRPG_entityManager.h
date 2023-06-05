
#ifndef WRPG_GAME_ENTITY_H
#define WRPG_GAME_ENTITY_H

#include <glib-2.0/glib.h>
#include "WRPG_MessageDispatcher.h"


enum {
  ent_Miner_Bob,
  ent_Elsa
};

static inline char* WRPG_GetNameOfEntity(int n) {
  switch(n) {
  case ent_Miner_Bob:
    return "Miner Bob";

  case ent_Elsa:
    return "Elsa"; 

  default:
    return "UNKNOWN!";
  }
}

typedef struct {

    int m_ID;

    char* m_entityName;

    void* m_pEntity; 

    void (*handleMessage)(void* entity, WRPG_Message* message);

} WRPG_gameEntity ;

typedef struct {

    GHashTable* mEntityMap;

} WRPG_EntityManager ;

void WRPG_EM_init(WRPG_EntityManager* em);

void WRPG_EM_RegisterEntity(WRPG_EntityManager* em, WRPG_gameEntity* NewEntity);

WRPG_gameEntity* WRPG_EM_GetEntityFromID(WRPG_EntityManager* em, int id);

void WRPG_EM_RemoveEntity(WRPG_EntityManager* em, WRPG_gameEntity* pEntity);

void WRPG_EM_Destroy(WRPG_EntityManager* em);


WRPG_gameEntity* WRPG_EM_newEntity(int id, char* entityName);

void WRPG_EM_freeEntity(WRPG_gameEntity* entity);


#endif 