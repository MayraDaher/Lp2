/******************************************************************************
aula 14 -barreiras  - segundo exemplo - Problema do sincronismo condicional - flags e coordenadores

Barreiras - As threads vão chegando e ficam bloqueadas até que todas as threads cheguem nesse ponto (barreira), finalizem seus
objetivos/atividade) e, então, elas são liberadas.

Essa solução utiliza arrays para que as threads armazenem seus estados de tal forma que não haja problema de contenção de memória. Pois,
assim, cada thread terá sua região de memória específica para manipular. 
Porém, se faz necessário criar uma thread coordenadora para controlar o que está acontecendo nesse arrays.


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

int arrive[QTD_THREADS];
int proceed[QTD_THREADS];

void* worker(void* p){
    long id = (long) p;
    while(1){
        /*código da tarefa */ 
        printf("[%ld] iniciando tarefa... \n", id);
        saida[id] = pow(entrada[id], 2);
        printf("[%ld] Tarefa: %d\n", id, entrada[id]);
        printf("[%ld] Resultado da tarefa: %d\n", saida[id]);
        sleep((int) (rand() % 3)); //Fim do código tarefa
        printf("[%ld] Embarreirada, esperando as demais!\n", id);
        arrive[id] = 1;
        while(proceed[id] != 1);  
        proceed[id] = 0;
        printf("[%ld] Saindo da barreira...\n", id);
    } 
    return 0;
}


void* coordinator(void* p){
    while(1){
        for(int i = 0; i < QTD_THREADS; i++){
            while(arrive[i] == 0);
            arrive[1] = 0;
        }
        printf("[coord] Barreira cheia, liberando...\n");
        for(int i = 0; i < QTD_THREADS; i++){
            proceed[i] = 1;
        }
    }
}

int main(void){
    pthread_t threads[QTD_THREADS];
    time_t t;
    pthread_t coord;
    
    srand((unsigned) time(&t));
    
    for (int i = 0; i < QTD_THREADS; i++)
    {
        entrada[i] = rand() % 100;
    }

    
    for(long i = 0; i < QTD_THREADS; i++){
        pthread_create(&threads[i], NULL, worker, (void*) i);
    }
    
    pthread_create(&coord, NULL, coordinator, NULL);
    
    sleep(15);
    return 0;
}
