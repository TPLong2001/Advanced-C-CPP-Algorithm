#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4 
#define NUM_INCREMENTS 30 

int counter = 0;
pthread_mutex_t lock;

void* increment(void* arg) {
    printf("--> Thread %d bắt đầu.\n", *(int*)arg);

    for (int i = 0; i < NUM_INCREMENTS; ++i) {
        pthread_mutex_lock(&lock);
        counter++;
        printf("counter thread %d: %d\n", *(int*)arg, counter);
        pthread_mutex_unlock(&lock);
    }
    printf(" xx Thread %d kết thúc.\n", *(int*)arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int pthread_ids[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, increment, &pthread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    printf("Giá trị counter cuối cùng là: %d\n", counter);

    return 0;
}