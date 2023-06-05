
#include <stdio.h>
#include <malloc.h>
#include "WRPG_entityManager.h"

WRPG_gameEntity* WRPG_EM_newEntity(int id, char* entityName) {

    WRPG_gameEntity* entity = (WRPG_gameEntity*) malloc(sizeof(WRPG_gameEntity));

    entity->m_ID = id;
    entity->m_entityName = entityName;
    entity->m_pEntity = NULL;

    return entity;

}

void WRPG_EM_freeEntity(WRPG_gameEntity* entity) {

    free(entity);

}