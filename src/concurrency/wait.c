#include <stdio.h>
#include <pthread.h>

struct semaphore_t {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int value;
};

void semaphore_init(struct semaphore_t *sem, int value) {
    pthread_mutex_init(&sem->lock, NULL);
    pthread_cond_init(&sem->cond, NULL);
    sem->value = value;
}

void semaphore_wait(struct semaphore_t *sem) {
    pthread_mutex_lock(&sem->lock);
    while (sem->value <= 0) {
        pthread_cond_wait(&sem->cond, &sem->lock);
    }
    sem->value--;
    pthread_mutex_unlock(&sem->lock);
}

void semaphore_post(struct semaphore_t *sem) {
    pthread_mutex_lock(&sem->lock);
    sem->value++;
    pthread_cond_signal(&sem->cond);
    pthread_mutex_unlock(&sem->lock);
}

struct semaphore_t sem_t;
static volatile int sum = 0;

void *mythread(void *arg) {
    printf("child is done.\n");
    semaphore_post(&sem_t);
    return NULL;
}


int main() {
    pthread_t th;
    semaphore_init(&sem_t, 0);
    pthread_create(&th, NULL, mythread, NULL);
    semaphore_wait(&sem_t);
    pthread_join(th, NULL);
    printf("parent is done");
    return 0;
}