#define _POSIX_TIMERS
#define _REENTRANT

#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct timespec start, end;
float etime;

int main()
{
   pid_t process_id;
   int process_numbers = 0;
   while (1)
   {
      if (clock_gettime(CLOCK_REALTIME, &start) < 0)
         printf("Error in clock\n");

      process_id = fork();
      process_numbers++;
      if (process_id == 0)
      {
         //Kill all children instantiated to avoid zombies
         kill(getpid(), SIGKILL);
      }
      if (process_id == -1)
      {
         printf("maximum number of processes: %d\n", process_numbers);
         printf("Processos Error ID: %d\n ", errno);
         printf("Error message: %s\n", strerror(errno));
         exit(0);
      }

      if (process_numbers == 1000)
      {
         if (clock_gettime(CLOCK_REALTIME, &end) < 0)
            printf("Error getting the time\n");

         etime = (end.tv_sec + end.tv_nsec / 10E9) - (start.tv_sec + start.tv_nsec / 10E9);
         printf("Time to create 1000 new process: %f\n", etime); // time to create 1000
      }
   }
}
