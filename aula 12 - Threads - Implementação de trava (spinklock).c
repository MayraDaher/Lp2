/******************************************************************************
Threads - Implementação de trava (spinklock)

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

int lock;
int varGlobal;

void* cs1(void* p){
    while(1){
        //<await (!lock) lock = 1; > //Protocolo de entrada
        while (lock == 1);  //Só progride quando in2 for diferente de 1printf("cs1 na seção crítica!\n");
        lock = 1; // Protocolo de saída
        printf("cs1 na seção crítica\n");
        varGlobal++;
        sleep(3);
        printf("[cs1] valor de varGlobal: %d\n", varGlobal);
        lock = 0;    //Protocolo de saída
        printf("cs1 fora da seção crítica\n\n");
        sleep(1);
        
    }
}


void* cs2(void* p){
    while(1){
        //await (!lock) lock = 1; >  //Protocolo de entrada
        while (lock == 1);  //Só progride quando in2 for diferente de 1
        lock = 1;
        printf("cs2 na seção crítica!\n");
        varGlobal++;
        sleep(3);
        printf("[cs2] Valor da varGlobal: %d\n", varGlobal);
        lock = 0;
        printf("cs2 fora da seção crítica\n\n");
        sleep(1);
        
    }
}

 int main(){

    pthread_t t1, t2;
    varGlobal = 0;
    lock = 0;
    
    pthread_create(&t1, NULL, cs1, NULL);
    pthread_create(&t2, NULL, cs2, NULL);
    
    sleep(20);
    
    return 0;
}