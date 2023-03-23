/******************************************************************************
Threads - Implementação de trava (lock) await - espera Ocupada - Protocolo de seção crítica 

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

int in1, in2;
int varGlobal;

void* cs1(void* p){
    while(1){
        //<await (!in2) in1 = 1; > //Protocolo de entrada
        while (in2 == 1);  //Só progride quando in2 for diferente de 1\n");
        in1 = 1; // Protocolo de saída
        printf("cs1 na seção crítica\n");
        varGlobal++;
        sleep(3);
        printf("[cs1] valor de varGlobal: %d\n", varGlobal);
        in1 = 0;    //Protocolo de saída
        printf("cs1 fora da seção crítica\n\n");
        sleep(1);
        
    }
}


void* cs2(void* p){
    while(1){
        //await (!in1) in2 = 1; >  //Protocolo de entrada
        while (in1 == 1);  //Só progride quando in2 for diferente de 1
        in2 = 1;
        printf("cs2 na seção crítica!\n");
        varGlobal++;
        sleep(3);
        printf("[cs2] Valor da varGlobal: %d\n", varGlobal);
        in2 = 0;
        printf("cs2 fora da seção crítica\n\n");
        sleep(1);
        
    }
}

 int main(){

    pthread_t t1, t2;
    varGlobal = 0;
    int in1, in2 = 0; 
    
    pthread_create(&t1, NULL, cs1, NULL);
    pthread_create(&t2, NULL, cs2, NULL);
    
    sleep(20);
    
    return 0;
}