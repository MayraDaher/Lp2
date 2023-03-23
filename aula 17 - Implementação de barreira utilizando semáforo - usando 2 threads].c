/******************************************************************************
Implementação de barreira utilizando semáforo - com flag de sincronização
exemplo com 2 threads

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

sem_t arrive1, arrive2;

void* worker1(void*p){
    int sl = rand() % 5;
    sl++;
    sleep(sl);
    printf("Worker 1 chegou na barreira\n");
    sem_post(&arrive1);
    sem_wait(&arrive2);
    printf("Worker 1 passou da barreira\n");
}

void* worker2(void* p){
    int sl = rand() % 5;
    sl++;
    sleep(sl);
    printf("Worker 2 chegou na barreira\n");
    sem_post(&arrive2);
    sem_wait(&arrive1);
    printf("Worker 2 passou da barreira\n");
}
int main()
{
    time_t t;    
    pthread_t thread1, thread2;
    
    sem_init(&arrive1, 0, 0);
    sem_init(&arrive2, 0, 0);
    
    srand(time(&t));
    
    pthread_create(&thread1, 0, worker1, 0);
    pthread_create(&thread2, 0, worker2, 0);
    
    pthread_join(thread1,0);
    pthread_join(thread2,0);
     
    
    
    return 0;
}