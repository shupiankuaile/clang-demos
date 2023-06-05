

#include <stdio.h>
#include <glib-2.0/glib.h>
#include "WRPG_consts.h"
#include "WRPG_entityManager.h"
#include "WRPG_MessageDispatcher.h"

extern WRPG_EntityManager gEntityManager;

void WRPG_DM_init(WRPG_MessageDispatcher* md) {

    md->mList = NULL;

}

static void WRPG_DM_discharge(WRPG_gameEntity* receiver, WRPG_Message* message) {

    receiver->handleMessage(receiver->m_pEntity, message);

}

void WRPG_DM_DispatchMessage(
                      WRPG_MessageDispatcher* md,
                       double  delay,
                       int    sender,
                       int    receiver,
                       WRPG_MessageType    msg,
                       void*  ExtraInfo) {
    
    //get pointers to the sender and receiver
  WRPG_gameEntity* senderEntity = WRPG_EM_GetEntityFromID(&gEntityManager, sender);
  WRPG_gameEntity* receiverEntity = WRPG_EM_GetEntityFromID(&gEntityManager, receiver);

  //make sure the receiver is valid
  if (receiverEntity == NULL) {
    printf(" Warning! No Receiver with ID of %d found \n", receiver);
    return;
  }
  
  //create the telegram
  WRPG_Message* message = (WRPG_Message*) malloc(sizeof(WRPG_Message));
  message->mSender = sender;
  message->mReceiver = receiver;
  message->msgType = msg;
  message->mExtraInfo = ExtraInfo;
  
  //if there is no delay, route telegram immediately                       
  if (delay <= 0.0f) {

    printf(" Instant telegram dispatched at time: %lld by %s for %s . Msg is %s .\n", 
                        g_get_real_time()/1000,
                        WRPG_GetNameOfEntity(senderEntity->m_ID),
                        WRPG_GetNameOfEntity(receiverEntity->m_ID),
                        WRPG_MsgToStr(msg)
                        );
    //send the message to the recipient
    WRPG_DM_discharge(receiverEntity, message);

  } else {//else calculate the time when the telegram should be dispatched

    gint64 CurrentTime = g_get_real_time()/1000; //ms

    message->mDispatchTime = CurrentTime + delay;

    //and put it in the queue
    md->mList = g_list_append(md->mList, message);

    printf(" Delayed telegram from %s recorded at time: %lld for %s . Msg is %s .\n", 
                        WRPG_GetNameOfEntity(senderEntity->m_ID),
                        g_get_real_time()/1000,
                        WRPG_GetNameOfEntity(receiverEntity->m_ID),
                        WRPG_MsgToStr(msg)
                        );    
  }

}

static int WRPG_DM_list_foreach_func(gpointer data) {

    gint64 CurrentTime = g_get_real_time()/1000; //ms

    WRPG_Message* message = (WRPG_Message*)data;

    WRPG_gameEntity* receiverEntity = WRPG_EM_GetEntityFromID(&gEntityManager, message->mReceiver);

    if(CurrentTime >= message->mDispatchTime) {
        //send the message to the recipient
        WRPG_DM_discharge(receiverEntity, message);

        printf(" Queued telegram ready for dispatch: Sent to  %s . Msg is %s .\n", 
                        WRPG_GetNameOfEntity(receiverEntity->m_ID),
                        WRPG_MsgToStr(message->msgType)
                        );

        return WRPG_TRUE;
    }

    return WRPG_FALSE;
}

void WRPG_DM_DispatchDelayedMessages(WRPG_MessageDispatcher* md) {

    int length = g_list_length(md->mList);
    printf(" Queued length before %d .\n", length);

    GList* iter= NULL;
    GList* removeList = NULL;

    for (iter = md->mList; iter != NULL; iter = iter->next) {
        
        int isDischarge = WRPG_DM_list_foreach_func(iter->data);
        if(isDischarge) {
            removeList = g_list_append(removeList, iter->data);
        }
    }


    if(removeList != NULL) {
        for (iter = removeList; iter != NULL; iter = iter->next) {
            md->mList = g_list_remove(md->mList, iter->data);
        }

        g_list_free(removeList);
    }


    length = g_list_length(md->mList);
    printf(" Queued length after %d .\n", length);

}

void WRPG_DM_destroy(WRPG_MessageDispatcher* md) {

    g_list_free(md->mList);

}