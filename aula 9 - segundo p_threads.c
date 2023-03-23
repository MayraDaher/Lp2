/******************************************************************************
Segundo exemplo thread_local

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define QTD_THREADS 5

long varGlobal;

void *funcao_thread(void *param){
    long id = (long)param;
    printf("[#%ld] Thread %ld criada!\n", id, id);
    sleep(5);
    varGlobal++;
    printf("[#%ld] varGlobal = %ld\n", id, varGlobal);
    pthread_exit((void*)varGlobal + id);
    
}
 
int main(void){
    pthread_t threads[QTD_THREADS];
    int thread_return[QTD_THREADS];
    
    varGlobal = 0;
    
    printf("[main] Iniciando thread principal...\n");
    printf("[main] criando %d threads...\n", QTD_THREADS);
    
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, funcao_thread, (void*) i+1);
        
    }
    //sleep(10);
    
    for(int i = 0; i < QTD_THREADS; i++){
        printf("[main] aguardando término da thread %d\n", (i+1));
        pthread_join(threads[i], (void*)&thread_return[i]);
        printf("[main] thread %d retornou %d\n", i, thread_return[i]);
        
    }
    printf("[main] finalizando thread principal...\n");
    
    return 0;
}