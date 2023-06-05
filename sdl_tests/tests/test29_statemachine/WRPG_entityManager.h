
#ifndef WRPG_GAME_ENTITY_H
#define WRPG_GAME_ENTITY_H

typedef struct {

    int m_ID;

    char* m_entityName;

    void* m_pEntity;

} WRPG_gameEntity ;

WRPG_gameEntity* WRPG_EM_newEntity(int id, char* entityName);

void WRPG_EM_freeEntity(WRPG_gameEntity* entity);


#endif 