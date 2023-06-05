
#ifndef WRPG_MESSAGE_DISPATCHER_H
#define WRPG_MESSAGE_DISPATCHER_H

#include <glib-2.0/glib.h>

typedef enum {
  Msg_HiHoneyImHome,
  Msg_StewReady
} WRPG_MessageType ;


static inline char* WRPG_MsgToStr(int msg) {
  switch (msg) {
  case 0:
    return "HiHoneyImHome"; 
  case 1:
    return "StewReady";
  default:
    return "Not recognized!";
  }
}

typedef struct {

    int mSender;

    int mReceiver;

    WRPG_MessageType msgType;

    double mDispatchTime;

    void* mExtraInfo;

} WRPG_Message ;


typedef struct {

    GList* mList;

} WRPG_MessageDispatcher ;

void WRPG_DM_init(WRPG_MessageDispatcher* messageDispatcher);

void WRPG_DM_DispatchMessage(
                      WRPG_MessageDispatcher* messageDispatcher,
                       double  delay,
                       int    sender,
                       int    receiver,
                       WRPG_MessageType    msgType,
                       void*  ExtraInfo);

void WRPG_DM_DispatchDelayedMessages(WRPG_MessageDispatcher* messageDispatcher);

void WRPG_DM_destroy(WRPG_MessageDispatcher* messageDispatcher);

#endif