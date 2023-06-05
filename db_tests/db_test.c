//
// Created by tjx on 11/2/22.
//

#include "db_test.h"

#include "dm_manager.h"

#include <stdio.h>

double queryYcId(connection_t *conn, char* tableName, char* columnName) {

    char sql[200];

    char* sqlFormat = "SELECT YC_ID FROM SG_DATACENTER.SVR_YC_SAMPLE_DEFINE WHERE HISTORY_TABLE_NAME = '%s' AND HISTORY_COLUMN_NAME = '%s';";
    sprintf(sql, sqlFormat, tableName, columnName);
    printf("sql:%s \n", sql);

    ddouble ycId = -1;
    slength ycIdInd = 0;

    DPIRETURN rt;

    dhstmt dpiHstmt;
    rt = dpi_alloc_stmt(conn->dpiHcon, &dpiHstmt);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_STMT, dpiHstmt);
        return ycId;
    }

    rt = dpi_exec_direct(dpiHstmt, sql);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_STMT, dpiHstmt);
        return ycId;
    }

    rt = dpi_bind_col(dpiHstmt, 1, DSQL_C_DOUBLE, &ycId, sizeof(ycId),&ycIdInd);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_STMT, dpiHstmt);
        return ycId;
    }

    ulength rowNum;

    while(dpi_fetch(dpiHstmt, &rowNum) != DSQL_NO_DATA) {
        printf("ycId = %f \n", ycId);
    }

    rt = dpi_free_stmt(dpiHstmt);
    if(!DSQL_SUCCEEDED(rt)){
        errMsgPrint(DSQL_HANDLE_STMT, dpiHstmt);
    }

    return ycId;
}