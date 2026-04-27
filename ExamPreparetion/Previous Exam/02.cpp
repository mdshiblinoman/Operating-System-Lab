/*
write a c program to show how data inconsistency can be crated by the concurrent
update of a global variable and solved by mutex in a multithreaded process.
main thread will wait for its child threads to be terminatted
*/

// Define POSIX feature macro for pthread function declarations
#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4
#define ITERATIONS 1000000

long long global_counter = 0;
pthread_mutex_t counter_mutex;

void *update_without_mutex(void *arg)
{
    (void)arg;
    for (int i = 0; i < ITERATIONS; i++)
    {
        global_counter++;
    }
    return NULL;
}

void *update_with_mutex(void *arg)
{
    (void)arg;
    for (int i = 0; i < ITERATIONS; i++)
    {
        pthread_mutex_lock(&counter_mutex);
        global_counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    long long expected = (long long)NUM_THREADS * ITERATIONS;

    printf("=== Concurrent update WITHOUT mutex ===\n");
    global_counter = 0;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, update_without_mutex, NULL) != 0)
        {
            perror("pthread_create failed");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter value: %lld\n", expected);
    printf("Actual counter value  : %lld\n", global_counter);
    printf("Data inconsistency can occur due to race condition.\n\n");

    printf("=== Concurrent update WITH mutex ===\n");
    global_counter = 0;

    if (pthread_mutex_init(&counter_mutex, NULL) != 0)
    {
        perror("pthread_mutex_init failed");
        return 1;
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_create(&threads[i], NULL, update_with_mutex, NULL) != 0)
        {
            perror("pthread_create failed");
            pthread_mutex_destroy(&counter_mutex);
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter value: %lld\n", expected);
    printf("Actual counter value  : %lld\n", global_counter);
    printf("Mutex ensures consistent update by protecting critical section.\n");

    pthread_mutex_destroy(&counter_mutex);
    return 0;
}
