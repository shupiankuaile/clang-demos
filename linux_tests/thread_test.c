//
// Created by tjx on 11/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include "thread_test.h"

int var_lock = 1;

struct tt_Message_st {
    int a;
    int b;
    pthread_key_t key;
    pthread_mutex_t lock;
    pthread_cond_t cond;
};

void* hello_thread(struct tt_Message_st* data) {
    fprintf(stdout, "hello_thread id:%lu \n", pthread_self());
    fprintf(stdout, "hello_thread a:%d, b:%d \n", data->a, data->b);

    //thread local
    printf("hello_thread id:%lu, pthread key :%d \n", pthread_self(), data->key);

    int local_data = 2;
    pthread_setspecific(data->key, &local_data);

    int* thread_data = (int*) pthread_getspecific(data->key);

    printf("hello_thread id:%lu, local_data:%lu \n", pthread_self(), *thread_data);

    //thread mutex and cond
    printf("hello_thread id:%lu, var_lock:%d \n", pthread_self(), var_lock);
    pthread_mutex_lock(&data->lock);
    var_lock++;
    printf("hello_thread id:%lu, var_lock:%d \n", pthread_self(), var_lock);

    pthread_cond_signal(&data->cond);

    pthread_mutex_unlock(&data->lock);



}

void test_pthread() {

    printf("------------test_pthread------------------- \n");

    struct tt_Message_st msg = {
            .a   = 1,
            .b  = 2,
    };

    int ret = pthread_key_create(&msg.key, NULL);
    if(ret != 0) {
        errno = ret;
        perror("pthread_key_create error");
        exit(EXIT_FAILURE);
    }

    ret = pthread_mutex_init(&msg.lock, NULL);
    if(ret != 0) {
        errno = ret;
        perror("pthread_mutex_init error");
        exit(EXIT_FAILURE);
    }

    ret = pthread_cond_init(&msg.cond, NULL);
    if(ret != 0) {
        errno = ret;
        perror("pthread_cond_init error");
        exit(EXIT_FAILURE);
    }

    printf("main thread id:%lu, pthread key :%d \n", pthread_self(), msg.key);

    pthread_t threadid;
    ret = pthread_create(&threadid, NULL, hello_thread, &msg);
    if (ret != 0) {
        errno = ret;
        perror("pthread_create error");
        exit(EXIT_FAILURE);
    }

    printf("main thread id:%lu, child thread id:%lu \n", pthread_self(), threadid);

    //thread local
    int local_data = 1;
    pthread_setspecific(msg.key, &local_data);

    int* thread_data = (int*) pthread_getspecific(msg.key);

    printf("main thread id:%lu, local_data:%lu \n", pthread_self(), *thread_data);


    //thread mutex
    printf("main thread id:%lu, var_lock:%d \n", pthread_self(), var_lock);
    pthread_mutex_lock(&msg.lock);
    var_lock++;
    printf("main thread id:%lu, var_lock:%d \n", pthread_self(), var_lock);

    //thread cond
    //pthread_cond_wait会释放互斥锁，然后阻塞等待
    pthread_cond_wait(&msg.cond, &msg.lock);
    //当被phread_cond_signal后，pthread_cond_wait会醒来，重新获取互斥锁

    printf("main thread id:%lu, var_lock:%d \n", pthread_self(), var_lock);

    pthread_mutex_unlock(&msg.lock);






    pthread_join(threadid, NULL);
    pthread_key_delete(msg.key);
    pthread_mutex_destroy(&msg.lock);
    pthread_cond_destroy(&msg.cond);

}