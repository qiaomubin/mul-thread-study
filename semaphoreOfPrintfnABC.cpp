#include<bits/stdc++.h>
#include<semaphore.h>
using namespace std;
sem_t  semA,semB,semC;
pthread_t  pa,pb,pc;

void* printA(void* arg)
{
    int n = (unsigned long long)arg;
    for(int i=1;i<=n;i++)
    {
        sem_wait(&semA);
         cout<<"A";
         sem_post(&semB);
    }
    pthread_exit(NULL);//退出线程
    
}

void* printB(void* arg)
{
    int n = (unsigned long long)arg;
    for(int i=1;i<=n;i++)
    {
        sem_wait(&semB);
         cout<<"B";
        sem_post(&semC);
    }
    pthread_exit(NULL);//退出线程
    
}

void* printC(void* arg)
{
    int n = (unsigned long long)arg;
    for(int i=1;i<=n;i++)
    {
       sem_wait(&semC);
       cout<<"C";
       sem_post(&semA);
    }
     pthread_exit(NULL);//退出线程
}
int main()
{
    int n;
    while(cin>>n)
    {
        sem_init(&semA,0,1);
        sem_init(&semB,0,0);
        sem_init(&semC,0,0);
        pthread_create(&pa,NULL,printA,(void*)(unsigned long long)(n));
        pthread_create(&pb,NULL,printB,(void*)(unsigned long long)(n));
        pthread_create(&pc,NULL,printC,(void*)(unsigned long long)(n));

        void * thread_ret;
        pthread_join(pa,&thread_ret);
        pthread_join(pb,&thread_ret);
        pthread_join(pc,&thread_ret);

        sem_destroy(&semA);
        sem_destroy(&semB);
        sem_destroy(&semC);

    }

}

