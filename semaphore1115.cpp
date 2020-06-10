/*
使用信号量解决力扣1115的交替打印问题
2020.6.28
乔畅
*/
#include<bits/stdc++.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<bits/stdc++.h>
#include <semaphore.h>
using namespace std;

#define THREAD_NUMBER 3 /* 进程/线程数 */
#define REPEAT_NUMBER 3 /* 每个进程/线程中的小任务数 */
#define DELAY_TIME_LEVELS 3.0 /*小任务之间的最大时间间隔*/

sem_t sem[THREAD_NUMBER];

void *thread_func(void *arg)
{
    int num = (unsigned long long)arg;

    /* 进行 P 操作 */
    sem_wait(&sem[num]);
    printf("Thread %d finished\n", num);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread[THREAD_NUMBER];
    int no = 0, res;
    void * thread_ret;
    srand(time(NULL));
    //创建线程
    for (no = 0; no < THREAD_NUMBER; no++)
    {
        sem_init(&sem[no], 0, 0);//初始化信号量
        res = pthread_create(&thread[no], NULL, thread_func, (void*)(unsigned long long)no);

        if (res != 0)
        {
            printf("Create thread %d failed\n", no);
            exit(res);
        }
    }

    printf("Create treads success\n Waiting for threads to finish...\n");
    for (no = 0; no < THREAD_NUMBER ; no++)
    {
         //进行 V 操作 
        sem_post(&sem[no]);
        res = pthread_join(thread[no], &thread_ret);
        if (!res)
        {
            printf("Thread %d joined\n", no);
        }
        else
        {
            printf("Thread %d join failed\n", no);
        }
      //sem_post(&sem[no+1]);
    }

    for (no = 0; no < THREAD_NUMBER; no++)
    {
        /* 删除信号量 */
        sem_destroy(&sem[no]);
    }

    return 0;
}