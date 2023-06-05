//
// Created by tjx on 11/9/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "time_test.h"

void test_time() {


    printf("------------test_time------------------- \n");
    time_t t;
    time(&t);

    printf("ctime: %s \n", ctime(&t));

    struct tm* tm = localtime(&t);

    printf("asctime: %s \n", asctime(tm));

    char tstrbuf[1024];
    strftime(tstrbuf, 1024, "%x %X", tm);
    printf("strftime: %s \n", tstrbuf);

}