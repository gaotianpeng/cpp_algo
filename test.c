#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;
volatile int done = 0;

void *mythread(void* arg) {
    printf("child thread done.\n");

    pthread_mutex_lock(&lock);
    // 唤醒父线程
    done = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_t p;
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&lock, NULL);
    pthread_create(&p, NULL, mythread, NULL);

    pthread_mutex_lock(&lock);
     (done == 0) {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);



    printf("parent is done.\n");
    pthread_join(p, NULL);
    
    return 0;
}


