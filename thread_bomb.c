#define _POSIX_TIMERS
#define _REENTRANT

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

void *thread_callback()
{
    pthread_t id = pthread_self();
}

struct timespec start, end;
float etime;

int main(int argc, char *argv[])
{
    int number_of_threads = 0;
    pthread_t *threads;

    while (1)
    {
        if (clock_gettime(CLOCK_REALTIME, &start) < 0)
            printf("Error getting the time\n");

        threads = (pthread_t *)realloc(threads, (number_of_threads + 1) * sizeof(pthread_t));

        if (pthread_create(&threads[number_of_threads], NULL, &thread_callback, NULL) != 0)
        {
            printf("Number of threads: %d\n", number_of_threads);
            printf("Processos Error ID: %d\n ", errno);
            printf("Error message: %s\n", strerror(errno));
            pthread_exit(0);
        }

        threads = threads;

        if (number_of_threads == 0)
        {
            if (clock_gettime(CLOCK_REALTIME, &end) < 0)
                printf("Error getting the time\n");

            etime = (end.tv_sec + end.tv_nsec / 10E9) - (start.tv_sec + start.tv_nsec / 10E9);
            printf("Time to create 1000 threads: %f\n", etime);
        }

        // free(threads);
        number_of_threads++;
    }
}
