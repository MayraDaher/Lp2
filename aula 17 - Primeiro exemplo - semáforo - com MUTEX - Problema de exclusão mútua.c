/******************************************************************************
Primeiro exemplo - semáforo - com MUTEX
Problema de exclusão mútua utilizando semáforo

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define QTD_THREADS 5

sem_t mutex;

int varGlobal = 0;
int repeat = 1;

void* cs(void* p){
    long index = (long) p;
    printf("[%ld] Iniciando... \n", index);
    while(repeat){
        sem_wait(&mutex);
        varGlobal++;
        printf("[%ld] alterou varGlobal para %d\n", index, varGlobal);
        sleep(1);
        sem_post(&mutex);
        sleep(1);
    }
    printf("[%ld] Finalizando...\n", index);
}

int main()
{
    pthread_t threads[QTD_THREADS];
    
    sem_init(&mutex, 0, 1);
    
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], 0, cs, (void*) i);
    }
    sleep(20);
    
    repeat = 0;
    
    sem_close(&mutex);
    sem_destroy(&mutex);
    
    sleep(5);
    
    return 0;
}
