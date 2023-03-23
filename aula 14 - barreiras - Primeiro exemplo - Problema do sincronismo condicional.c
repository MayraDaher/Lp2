/******************************************************************************
Primeiro exemplo - Problema do sincronismo condicional - barreiras 
Barreiras - As threads vão chegando e ficam bloqueadas até que todas as threads cheguem nesse ponto (barreira), finalizem seus
objetivos/atividade) e, então, elas são liberadas.


process worker[i=1 to n]{
    while(true){
        código da tarefa i;
        FA(count, 1);
        while(count!= n) skip;           //espera pelo término de todas as tarefas;
    }
}


*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define QTD_THREADS 5

int entrada[QTD_THREADS];
int saida[QTD_THREADS];
int count;


void* processa_parte(void* p){
    long id = (long) p;
    while(1){
        /*código da tarefa */ 
        printf("[%d] iniciando tarefa... \n", id);
        saida[id] = pow(entrada[id], 2);
        printf("[%d] Tarefa: %d\n", id, entrada[id]);
        printf("[%d] Resultado da tarefa: %d\n", saida[id]);
        sleep((int) (rand() % 3)); //Fim do código tarefa
        printf("[%d] Embarreirada, esperando as demais!\n", id); 
        /* Ponto de embarreiramento */ 
        __sync_fetch_and_add(&count, 1);
        while((count % QTD_THREADS) != 0);
        
    }
}
int main()
{
    pthread_t threads[QTD_THREADS];
    time_t t;
    count = 0;
    
    srand((unsigned) time(&t));
    
    for(int i = 0; i < QTD_THREADS; i++){
        entrada[i] = rand() % 100;
    }
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, processa_parte, (void*) i);
    }
    
    sleep(30);
    return 0;
}
