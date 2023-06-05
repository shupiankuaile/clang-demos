
#include <stdio.h>
#include <malloc.h>
#include <glib-2.0/glib.h>
#include "WRPG_entityManager.h"
#include "WRPG_consts.h"

static void WRPG_EM_printKeyWhenRemove(gpointer data) {

    printf("We free key: %d /n", *(gint*)data);

}

static void WRPG_EM_freeValueWhenRemove(gpointer data) {

    WRPG_EM_freeEntity((WRPG_gameEntity*) data);

}

void WRPG_EM_init(WRPG_EntityManager* em) {

    GHashTable* hash = g_hash_table_new_full(g_int_hash, 
                                        g_int_equal, 
                                        &WRPG_EM_printKeyWhenRemove, 
                                        &WRPG_EM_freeValueWhenRemove);

    em->mEntityMap = hash;

}

void WRPG_EM_RegisterEntity(WRPG_EntityManager* em, WRPG_gameEntity* NewEntity) {

    g_hash_table_insert(em->mEntityMap, &NewEntity->m_ID, NewEntity);

}

WRPG_gameEntity* WRPG_EM_GetEntityFromID(WRPG_EntityManager* em, int id) {

    gpointer data = g_hash_table_lookup(em->mEntityMap, &id);

    return (WRPG_gameEntity*) data;

}

void WRPG_EM_RemoveEntity(WRPG_EntityManager* em, WRPG_gameEntity* pEntity) {

    g_hash_table_remove(em->mEntityMap, &pEntity->m_ID);

}

static gboolean WRPG_EM_foreachDestroyKeyValue(gpointer key, gpointer value, gpointer user_data) {
    printf("We destroy key: %d /n", *(gint*)key);
    WRPG_EM_freeEntity((WRPG_gameEntity*) value);

    return WRPG_TRUE;
}

void WRPG_EM_Destroy(WRPG_EntityManager* em) {

    g_hash_table_foreach_remove(em->mEntityMap, &WRPG_EM_foreachDestroyKeyValue, NULL);

    g_hash_table_destroy(em->mEntityMap);
}

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