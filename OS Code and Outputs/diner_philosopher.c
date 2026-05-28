#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define N 5  

pthread_mutex_t forks[N];
sem_t room;  

void think(int i) {
    printf("Philosopher %d is THINKING\n", i);
    sleep(1);
}

void eat(int i) {
    printf("Philosopher %d is EATING\n", i);
    sleep(1);
}

void* philosopher(void* arg) {
    int i = *(int*)arg;

    while (1) {
        think(i);

        sem_wait(&room);

        pthread_mutex_lock(&forks[i]);
        printf("Philosopher %d picked LEFT fork %d\n", i, i);

        pthread_mutex_lock(&forks[(i + 1) % N]);
        printf("Philosopher %d picked RIGHT fork %d\n", i, (i + 1) % N);

        eat(i);

        pthread_mutex_unlock(&forks[(i + 1) % N]);
        printf("Philosopher %d put RIGHT fork %d\n", i, (i + 1) % N);

        pthread_mutex_unlock(&forks[i]);
        printf("Philosopher %d put LEFT fork %d\n", i, i);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
        sem_post(&room);

        sleep(1);
    }
}

int main() {
    pthread_t threads[N];
    int ids[N];

    // initialize forks
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // initialize room semaphore to N-1 (4)
    sem_init(&room, 0, N - 1);

    // create threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // join threads (runs forever)
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}