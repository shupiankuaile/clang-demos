//
// Created by tjx on 11/1/22.
//

#ifndef MY_TOOLS_DM_MANAGER_H
#define MY_TOOLS_DM_MANAGER_H

#include <DPI.h>
#include <DPIext.h>
#include <DPItypes.h>

typedef struct connection_st connection_t ;
struct connection_st {
    dhenv dpiHenv;
    dhcon dpiHcon;
};


void initConn(connection_t *conn);

void freeConn(connection_t *conn);

void errMsgPrint(sdint2 hndl_type, dhandle hndl);


#endif //MY_TOOLS_DM_MANAGER_H
