/******************************************************************************
aula 15 - Solução para algoritmo do Ticket - usando MUTEX 


*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define QTD_THREADS 5

int varGlobal = 0;
int number = 1;         //Variáveis utilizadas para o Ticket
int next = 1;           //Variáveis utilizadas para o Ticket
int turn[QTD_THREADS];  //Array que define a vez

pthread_mutex_t number_inc_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condicao_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condicao_cond = PTHREAD_COND_INITIALIZER;        //Variável condicional

void* cs(void* p)
{
    lond idx = (long) p;
    
    while(1)
    {
        pthread_mutex_lock(&number_inc_mutex);              //Acontecem de forma atômica
        number++;                                           //Acontecem de forma atômica
        turn[idx] = number;                                 //Acontecem de forma atômica
        pthread_mutex_unlock(&number_inc_mutex);            //Acontecem de forma atômica
        
        pthread_mutex_lock(&condicao_mutex);
        if(turn[idx] % next == 0){
            pthread_cond_signal(&condicao_cond_;
        }    
        else{
            pthread_cond_wait(&condicao_cond, &condicao_mutex);
        }    
        
        varGlobal++;
        printf("[CS %ld] ALterou o valor para: %d\n", idx, varGlobal);
        puts("..");
        
        pthread_mutex_lock(&number_inc_mutex);  
        next++;
        turn[idx] - number;
        pthread_mutex_unlock(&number_inc_mutex);
        
        pthread_mutex_unlock(&condicao_mutex);
        
    
    }
    return 0;
}

int main()
{
    pthread_t thread[QTD_THREADS];
    
    for(int i = 0; i < QTD_THREADS; i++)
        turn[i] = 0;
        
    for(long i = 0; i < QTD_THREADS; i++)
        pthread_create(&thread[i], NULL, cs, (void*) i);

    sleep(10);
    
    return 0;
}
