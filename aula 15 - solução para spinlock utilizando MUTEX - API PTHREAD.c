/******************************************************************************
aula 15 - spinlock com MUTEX 


*******************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

int lock = 0;
int varGlobal = 0;

pthread_mutex_t mutex_lock_control = PTHREAD_MUTEX_INITIALIZER; //inicialização da variável de controle mutex_lock_control

void* cs(void* p)
{
    long idx = (long) p;
    printf("[CS-%ld] Iniciando...\n", idx);
    
    while(1){
    
    pthread_mutex_lock(&mutex_lock_control);    //Protocolo de entrada
    varGlobal++;                                //Início da secção crítica
    printf("[CS %ld] Alterou o valor para %d\n", idx, varGlobal);
    puts("..");
    usleep(900000);
    //sleep(1); //Descomente para gerar STARVATION
    
    // Fim da seção crítica
    
    pthread_mutex_unlock(&mutex_lock_control);  //Protocolo de saída
    }
    return 0;
}
 

int main()
{
    pthread_t thread[5];
    
    for(long i = 0; i < 5; i++){
        pthread_create(&thread[i], NULL, cs, (void*) i);
    }
    sleep(20);   
    return 0;
}
