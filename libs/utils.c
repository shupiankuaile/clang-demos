//
// Created by tjx on 11/8/22.
//

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "utils.h"

#define UTILS_MAX_LINE 1024

long utils_read_file(char* filename, char* buf) {

    FILE *fp = fopen(filename,"r");
    if(fp == NULL) {
        fprintf(stderr, "File Not Found, error:%s \n", strerror(errno));
        return -1L;
    }


    long filesz = utils_file_size(filename);
    printf("file_size:%ld \n",filesz);

    char linebuf[UTILS_MAX_LINE];
    char* line = NULL;
    while((line = fgets(linebuf, UTILS_MAX_LINE, fp)) != NULL) {
//        printf("line:%s \n", line);
        strcat(buf, line);
    }

    fclose(fp);

    return filesz;
}

long utils_file_size(char* filename) {

    struct stat file_stat;
    int ret = stat(filename, &file_stat);
    if(ret < 0) {
        fprintf(stderr, "File Not Found, error:%s \n", strerror(errno));
        return ret;
    }

    return file_stat.st_size;
}