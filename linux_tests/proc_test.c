//
// Created by tjx on 11/10/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "proc_test.h"

void test_proc() {

    printf("------------test_proc------------------- \n");

    //fork wait
    pid_t pid = fork();
    if(pid < 0) {
        fprintf(stderr, "fork error: %s \n", strerror(errno));
        return;
    } else if(pid == 0) {
        fprintf(stdout, "child proc: %d \n", getpid());
        exit(2);
    } else {

        fprintf(stdout, "parent proc: %d \n", getpid());

        int status;
        pid_t cpid = wait(&status);
        fprintf(stdout, "exit child proc: %d with status: %d, exited normal:%d \n", cpid, status, WIFEXITED(status));
    }

    //exec

    pid_t cpid = fork();
    if(cpid < 0) {
        perror("fork error");
    } else if(cpid == 0) {
        fprintf(stdout, "child pid:%d \n", getpid());
        fflush(stdout);

        execl("/bin/ls", "ls", "-la", "/home", NULL);

        exit(1);
    } else {

        fprintf(stdout, "parent pid: %d \n", getpid());

        int status;
        cpid = wait(&status);
        fprintf(stdout, "exit child proc: %d with status: %d, exited normal:%d \n", cpid, status, WIFEXITED(status));
    }


    //system
    int status = system("ls -la /home");
    fprintf(stdout, "system exit with status:%d \n", status);
}