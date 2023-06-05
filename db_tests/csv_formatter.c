//
// Created by tjx on 11/1/22.
//

#include "csv_formatter.h"

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>

#define MAX_PATH 1024
#define MAX_LINE 1024

static void dirWalk(char *dir, char* files[]);
static void formatFileTo(FILE* srcFile, FILE* destFile);
static char* formatLine(char* srcLine, char* destLine);

void doFormat(char* srcDir, char* destDir) {

    char* fileNames[1024];

    dirWalk(srcDir, fileNames);

    char srcFilePath[MAX_PATH];
    char destFilePath[MAX_PATH];

    char* fileName = NULL;
    int fileNo = 0;
    while((fileName = fileNames[fileNo]) != NULL) {

        printf("Start format file: %s \n", fileName);

        sprintf(srcFilePath, "%s/%s", srcDir, fileName);
        sprintf(destFilePath, "%s/%s", destDir, fileName);

        FILE* srcFile = fopen(srcFilePath, "r");
        FILE* destFile = fopen(destFilePath, "w+");

        formatFileTo(srcFile, destFile);

        fclose(srcFile);
        fclose(destFile);

        fileNo++;
    }

    printf("Found %d files. \n", fileNo);

}

static void formatFileTo(FILE* srcFile, FILE* destFile) {
    char srcLineBuffer[MAX_LINE];
    char destLineBuffer[MAX_LINE];

    char* srcLine = NULL;
    char* destLine = NULL;
    while((srcLine = fgets(srcLineBuffer, MAX_LINE, srcFile)) != NULL) {
        destLine = formatLine(srcLine, destLineBuffer);

        fputs(destLine, destFile);
    }
}

static char* formatLine(char* srcLine, char* destLine) {

    char* delimiter = ",";

    char* tokenPtr = strtok(srcLine, delimiter);
    int columnNo = 0;
    while (tokenPtr != NULL) {

        if(columnNo == 0) {
            sprintf(destLine, "%s", tokenPtr);
        } else {
            strcat(destLine, tokenPtr);
        }

        tokenPtr = strtok(NULL, delimiter);

        if(columnNo == 0) {
            strcat(destLine, ",");
        } else if (tokenPtr != NULL) {
            strcat(destLine, ",1,");
        }

        columnNo++;
    }

    return destLine;

}

static void dirWalk(char *dir, char* files[])
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
        fprintf(stderr, "dirWalk:can not open %s\n", dir);
        return;
    }

    int fileNo = 0;
    while ((dp = readdir(dfd)) != NULL) {
        if (strstr(dp->d_name, ".csv") == NULL) {
            continue;
        }

        sprintf(name, "%s", dp->d_name);

        void* fileName = malloc(strlen(name)+1);
        strcpy(fileName, name);

        files[fileNo] = fileName;
        fileNo++;
    }
    closedir(dfd);
}

