/******************************************************************************
Primeiro exemplo - Algoritmo do ticket
*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define QTD_THREADS 5

int varGlobal = 0; 
int number = 0;
int next = 0; 
int turn[QTD_THREADS] = {0,0,0,0,0};

void* funcao_secao_critica(void* p)
{
    long id = (long) p;
    while(1)
    {
        turn[id] = __sync_fetch_and_add(&number, 1); // Protocolo de entrada
        while(turn[id] != next)
            ;                                       //Protocolo de entrada
        varGlobal++;                                //Seção crítica
        printf("[%ld] varGlobal = %d\n", id, varGlobal);
        sleep(1);
        next++;                                     //Protocolo de saída 

    }    
}

int main(void)
{
    pthread_t threads[QTD_THREADS];
    
    printf("[main] Algoritmo do ticket\n");
    
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, funcao_secao_critica, (void*) i);
    }
    
    for(int i = 0; i < QTD_THREADS; i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}