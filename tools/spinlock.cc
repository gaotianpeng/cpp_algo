//
// Created by gtp on 2023/3/19.
//
#include <atomic>
#include <chrono>
#include <thread>

/*
    自旋锁，是一个锁的概念，它表示一个线程在无法获取到锁时，不进行挂进等待，
    而是通过不断的循环来重复获取锁，使用自旋锁通常需要确保锁不会被其它线程占用过长时间。
    同时也不能出现死锁情况。否则自旋锁的效率会很低

    CAS（compare and swap）
        CAS 是一个比较并交换的操作，能够在保证原子性的情况下处理数据的修改的操作，
        在处理器支持该指令时，能到以无锁的方式进行（效率更高）
        其基本原理为在对一个变量进行修改操作时，先读取这个变量，
        随后进行变量的计算操作，最后在把这个操作的值写回到变量。
        不过其会在写入之前检查数据和刚开始相比有没有改变，
        如果数据已经被其它线程改变，则此次修改失败，并尝试重试。
 */
class spinlock {
public:
    spinlock();
    void lock();
    void unlock();

    std::atomic_flag flag;
};

spinlock::spinlock() : flag(ATOMIC_FLAG_INIT) {
}

void spinlock::lock() {
    while (flag.test_and_set(std::memory_order_acquire)) {
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

void spinlock::unlock() {
    flag.clear(std::memory_order_release);
}
