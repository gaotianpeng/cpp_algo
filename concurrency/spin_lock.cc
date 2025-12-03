#include <iostream>
#include <thread>
#include <atomic>


struct lock_t {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

void lock(lock_t* l) {
    while (l->flag.test_and_set(std::memory_order_acquire)) {
        ;
    }
}

void unlock(lock_t* l) {
    l->flag.clear(std::memory_order_release);
}

// int TestAndSet(int* old, int newv) {
// 	int old_value = *old;
// 	*old = newv;
// 	return old_value;
// }


// void lock(lock_t* l) {
// 	while (l->flag) {
// 		;
// 	}

// 	l->flag = 1;
// }

// void lock(lock_t* l) {
// 	while (TestAndSet(&l->flag, 1) == 1) {
// 		;
// 	}
// }

// void unlock(lock_t* l) {
// 	l->flag = 0;
// }


// void lock(lock_t* l) {
//  	while (__sync_lock_test_and_set(&l->flag, 1)) {
// 		;
// 	}
// }

// void unlock(lock_t* l) {
// 	__sync_lock_release(&l->flag);
// }


static volatile int sum = 0;
struct lock_t l;

void mythread() {
	for (int i = 0; i < 10000; i++) {
		lock(&l);
		sum = sum + 1;
		unlock(&l);
	}

}

int main() {
    std::thread th1(mythread);
	std::thread th2(mythread);
	th1.join();
	th2.join();
	std::cout << "sum = " << sum << std::endl;
	
	return 0;
}