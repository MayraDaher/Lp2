/******************************************************************************
Implementação de barreira utilizando semáforo - com flag de sincronização
exemplo com array de threads

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define QTD_THREADS 5 

sem_t arrive[QTD_THREADS];

void* worker(void*p){
    long index = (long) p;
    int sl = rand() % 5;
    sl++;
    printf("Worker %ld: tarefa de %d segundos\n", index, sl);
    sleep(sl);
    printf("Worker %ld chegou na barreira\n", index);
    sem_post(&arrive[index]);
    for(int i = 0; i < QTD_THREADS; i++){
        if(i != index){
            int sem_v;
            sem_getvalue(&arrive[i], &sem_v);
            if(sem_v != 0)
                sem_wait(&arrive[i]);
        }
    }
    printf("Worker %ld passou da barreira\n", index);
}


int main()
{
    time_t t;    
    pthread_t thread[QTD_THREADS];
    
    for(int i = 0; i < QTD_THREADS; i++){
        sem_init(&arrive[i], 0, 0);    
    }
    
    srand(time(&t));
    
    for(int i = 0; i < QTD_THREADS; i++){
        pthread_create(&thread[i], 0, worker, (void*)i);
    }
    
    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(thread[i],0);
    }
     
    
    return 0;
}