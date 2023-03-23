#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define QTD_THREADS 500
#define QTD_ADD 100

long var_global;

void *funcao_thread(void *param)
{
    long id = (long)param;
    printf("[%d] Thread criada!\n", id);

    for (int i = 0; i < QTD_ADD; i++)
    {
        __sync_fetch_and_add(&var_global, 1);
       // var_global++;
        //var_global = var_global + 1;
    }

    printf("[%d] Thread finalizando...\n", id);
    pthread_exit((void *)var_global);
}

int main(void)
{
    pthread_t threads[QTD_THREADS];
    int result[QTD_THREADS];

    var_global = 0;

    for (long i = 0; i < QTD_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, funcao_thread, (void *)i);
    }

    for (int i = 0; i < QTD_THREADS; i++)
    {
        pthread_join(threads[i], (void *)&result[i]);
        printf("[main] resultado recebido da thread %ld: %d\n",
               i, result[i]);
    }

    printf("[main] Valor final da variavel global = %d\n", var_global);

    return 0;
}