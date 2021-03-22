

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

int *threadInfo()
{
    pthread_t id = pthread_self();
    return id
    // printf("Sucess creating the %ld thread.\n", id);
}

int main(int argc, char *argv[])
{
    int nThreads = 0;
    pthread_t *threads;
    while (1)
    {

        threads = (pthread_t *)realloc(threads, (nThreads + 1) * sizeof(pthread_t)); // Giving more memory to thread array

        if (pthread_create(&threads[nThreads], NULL, &threadInfo, NULL) != 0)
        {
            printf("nThread: %d\n", nThreads);
            printf("Processos Error ID: %d\n ", errno);
            printf("Error message: %s\n", strerror(errno));
            pthread_exit(0);
        }

        threads = threads;

        nThreads++;
    }
}
