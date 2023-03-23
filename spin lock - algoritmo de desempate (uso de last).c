/******************************************************************************
Quarto exemplo spin_lock (algoritmo de desempate - last - solução mais justa e otimizada) - com 2 threads
Nesse caso temos 2 threadas. Logo, 2 variáveis in. 
Caso prescise de mais threads, quant (threads) == quant(in's).
*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

int in1, in2;
int last = 1;
int varGlobal;

void* cs1(void* p){
    while(1){
        last = 1, in1 = 1;
        //Protocolo de entrada/
        while (in2 == 1 && last == 1)
            ;  //Só progride quando in2 for diferente de 1\n");
        
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
        last = 2; in2 =  1;
        //Protocolo de entrada
        while (in1 == 1 && last == 2)
            ;  //Só progride quando in1 for diferente de 1
        
        printf("cs2 na seção crítica!\n");
        varGlobal++;
        sleep(3);
        printf("[cs2] Valor da varGlobal: %d\n", varGlobal);
        in2 = 0;    //protocolo de saída
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
