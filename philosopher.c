#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h> 
#define NUMP 5
pthread_mutex_t fork_mutex[NUMP];
pthread_mutex_t eat_mutex;
pthread_cond_t space_avail = PTHREAD_COND_INITIALIZER;
int num_diners = 0;
void *diner(void *arg)
{
        uintptr_t philo;
        philo = (uintptr_t) arg;
        int eating = 0;
        printf("I'm diner %d\n", philo);
        while (eating < 5) {
                printf("%d is thinking\n", philo);
                sleep( philo / 2 );
                printf("%d is hungry\n", philo );
                pthread_mutex_lock(&eat_mutex);
                if (num_diners == (NUMP - 1))
                        pthread_cond_wait(&space_avail, &eat_mutex);
                num_diners++;
                pthread_mutex_unlock(&eat_mutex);
                pthread_mutex_lock(&fork_mutex[philo]);
                pthread_mutex_lock(&fork_mutex[( philo + 1) % NUMP]);
                printf("%d is eating\n", philo);
                eating++;
                sleep(1);
                printf("%d is done eating\n", philo);
                pthread_mutex_unlock(&fork_mutex[philo]);
                pthread_mutex_unlock(&fork_mutex[(philo + 1)%NUMP]);
                pthread_mutex_lock(&eat_mutex);
                if (num_diners == (NUMP - 1))
                        pthread_cond_signal(&space_avail);
                num_diners--;
                pthread_mutex_unlock(&eat_mutex);
                }
        pthread_exit(NULL);
}
int main()
{
        uintptr_t i;
        pthread_t diner_thread[NUMP];
        pthread_mutex_init(&eat_mutex, NULL);
        for (i=0; i < NUMP; i++)
                pthread_mutex_init(&fork_mutex[i], NULL);
        for (i=0; i < NUMP; i++){
                pthread_create(&diner_thread[i], NULL, diner, (void *) i);
        }
        for (i=0; i < NUMP; i++)
                pthread_join(diner_thread[i], NULL);
        exit(EXIT_SUCCESS);
}