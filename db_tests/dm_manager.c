//
// Created by tjx on 11/2/22.
//

#include "dm_manager.h"

#include <stdio.h>
#include <stdlib.h>

void initConn(connection_t *conn) {

    DPIRETURN rt;

    rt = dpi_alloc_env(&conn->dpiHenv);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_ENV, conn->dpiHenv);
        exit(-1);
    }

    rt = dpi_alloc_con(conn->dpiHenv, &conn->dpiHcon);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_DBC, conn->dpiHcon);
        exit(-1);
    }

    dpi_set_con_attr(conn->dpiHcon, DSQL_ATTR_LOGIN_PORT, 5236, 0);
    /*连接到本地服务器*/
    if(!DSQL_SUCCEEDED(dpi_login(conn->dpiHcon,"127.0.0.1","SYSDBA","SYSDBA"))) {
        errMsgPrint(DSQL_HANDLE_DBC, conn->dpiHcon);
        /*释放连接句柄*/
        dpi_free_con(conn->dpiHcon);
        /*释放环境句柄*/
        dpi_free_env(conn->dpiHenv);
        exit(-1);
    }

}


void freeConn(connection_t *conn) {

    DPIRETURN rt;

    /*断开与数据源之间的连接*/
    rt = dpi_logout(conn->dpiHcon);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_DBC, conn->dpiHcon);
        exit(-1);
    }

    /*释放连接句柄*/
    rt = dpi_free_con(conn->dpiHcon);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_DBC, conn->dpiHcon);
        exit(-1);
    }

    /*释放环境句柄*/
    rt = dpi_free_env(conn->dpiHenv);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_ENV, conn->dpiHenv);
        exit(-1);
    }
}

void errMsgPrint(sdint2 hndl_type, dhandle hndl) {
    sdint4 err_code;
    sdint2 msg_len;
    sdbyte err_msg[SDBYTE_MAX];
    /* 获取错误信息字段 */
    /*
    dpi_get_diag_field(hndl_type, hndl, 1, DSQL_DIAG_MESSAGE_TEXT, err_msg,
    sizeof(err_msg), NULL);
    printf("err_msg = %s\n", err_msg);*/
    /* 获取错误信息集合 */
    dpi_get_diag_rec(hndl_type, hndl, 1, &err_code, err_msg, sizeof(err_msg),&msg_len);
    printf("err_msg = %s, err_code = %d\n", err_msg, err_code);
}
