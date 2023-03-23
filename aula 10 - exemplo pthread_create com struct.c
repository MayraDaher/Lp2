/******************************************************************************
Terceiro exemplo Threads
pthread_create recebendo struct como parâmetro

*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

typedef struct
{
    int inicio;
    int fim;
}t_dois_num;

void* funcao_concorrente(void* p){
    t_dois_num* params = (t_dois_num*) p;
    int start = params -> inicio;
    int end = params -> fim;
    long i;
    
    for(i = start; i <= end; i++){
        printf("fc: %ld\n", i);
        sleep(1);
    }
    pthread_exit((void*)i);
    
}

int funcao_sequencial(int inicio, int fim){
    int i;
    for(i= inicio; i <= fim; i++){
        printf("fs: %d\n", i);
        sleep(1);
    }
    return i;
}


int main()
{
    pthread_t t1;
    t_dois_num param;
    long res_c;
    int res_s;
    
    param.inicio = 1;
    param.fim = 10;
    
    pthread_create(&t1, NULL, funcao_concorrente, (void*) &param);
    
    res_s = funcao_sequencial(0,3);
    
    
    printf("[main] res_c = %ld\n", res_c);
    printf("[main] res_s = %d\n", res_s);
    
    return 0;
}
