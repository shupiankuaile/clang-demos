//
// Created by tjx on 11/10/22.
//

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


#include "dir_test.h"

void test_dir() {

    printf("------------test_dir------------------- \n");
    char* dirname = "/home/tjx/Workspace/workspace";
    DIR* dir =  opendir(dirname);

    struct dirent* dir_ent = NULL;
    while((dir_ent = readdir(dir)) != NULL) {
        printf("file_name:%s \n", dir_ent->d_name);
    }
    closedir(dir);

    char* tmp_dir = "/tmp/test_4_mkdir";
    mkdir(tmp_dir, ACCESSPERMS);

    remove(tmp_dir);

    char cwd_buf[1024];
    printf("cwd: %s \n", getcwd(cwd_buf, sizeof(cwd_buf)));
}