//
// Created by tjx on 11/9/22.
//
#include <stdio.h>

#include "test_suite.h"
#include "time_test.h"
#include "dir_test.h"
#include "proc_test.h"
#include "thread_test.h"

void test_all() {

    test_time();

    test_dir();

    test_proc();

    test_pthread();

    printf("------------test end------------------- \n");
}