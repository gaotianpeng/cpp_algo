#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <queue>

using namespace std;

struct semaphore_t {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int value;
};

void semaphore_init(semaphore_t *sem, int value) { 
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

struct queue_t {
    queue<int> q;
    int size;
    pthread_mutex_t lock;
    semaphore_t data_num;
    semaphore_t free_queue_len;
};

void init_queue(struct queue_t *q, int size) {
    q->size = size;
    pthread_mutex_init(&q->lock, NULL);
    semaphore_init(&q->data_num, 0);
    semaphore_init(&q->free_queue_len, size);
}

void push(struct queue_t *q, int data) {
    semaphore_wait(&q->free_queue_len);
    pthread_mutex_lock(&q->lock);
    q->q.push(data);
    pthread_mutex_unlock(&q->lock);
    semaphore_post(&q->data_num);
}

int pop(struct queue_t *q) {
    int res;
    semaphore_wait(&q->data_num);
    pthread_mutex_lock(&q->lock);
    res = q->q.front();
    q->q.pop();
    pthread_mutex_unlock(&q->lock);
    semaphore_post(&q->free_queue_len);

    return res;
}

void* consumer_thread(void *arg) {
    struct queue_t *q = (struct queue_t *)arg;
    while (1) {
        int data = pop(q);
        printf("consumer get data: %d\n", data);
        // 模拟处理数据需要的时间
        sleep(2);
    }
    return NULL;
}

void* product_thread(void* arg) {
    struct queue_t *q = (struct queue_t *)arg;
    int i = 0;
    while (1) {
        push(q, i);
        printf("product push data: %d\n", i);
        i++;
    }

    return NULL;
}

int main() {
    pthread_t consumer, producer;
    struct queue_t q;
    init_queue(&q, 2);

    pthread_create(&consumer, NULL, consumer_thread, &q);
    pthread_create(&producer, NULL, product_thread, &q);

    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);
    return 0;
}