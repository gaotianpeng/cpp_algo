//
// Created by gtp on 2023/3/15.
//

#include "thread_pool.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <queue>
#include <thread>

class ThreadPool::Impl {
public:
    Impl(int thread_num): thread_num_(thread_num) {
        is_available_.store(true);
        is_stop_.store(false);
    }

    ~Impl() {
    }

    void AddTask(std::function<void()> task) {
        {
            std::lock_guard<std::mutex> lock(this->task_mutex_);
            task_queue_.emplace(task);
//            std::cout<< task_queue_.size();
        }
        this->task_cv_.notify_one();
    }

    bool Start() {
        if (!IsAvailable()) {
            return false;
        }
        for (int i = 0; i < thread_num_; ++i) {
            workers_.emplace_back(
                [this]() {
                    for(;;) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> locker(task_mutex_);
                            task_cv_.wait(locker, [this]() {
                                return is_stop_.load() || !task_queue_.empty();
                            });
                        }

                        if (is_stop_.load()) {
                            break;
                        }

                        if (!task_queue_.empty()) {
                            task = std::move(task_queue_.front());
                            task_queue_.pop();
                            task();
                        }
                    }
                }
            );
        }

        return true;
    }
    bool Stop() {
        is_stop_.store(true);
        is_available_.store(false);
        task_cv_.notify_all();

        for (auto& elem: workers_) {
            if (elem.joinable()) {
                elem.join();
            }
        }

        return true;
    }

    bool IsAvailable() {
        return is_available_.load();
    }

private:
    int thread_num_;
    std::atomic_bool is_available_;
    std::atomic_bool is_stop_;
    std::mutex task_mutex_;
    std::condition_variable task_cv_;
    std::queue<std::function<void()>> task_queue_;
    std::vector<std::thread> workers_;
};

ThreadPool::ThreadPool(int thread_num) {
    impl_.reset(new Impl(thread_num));
}

ThreadPool::~ThreadPool() {
}

void ThreadPool::AddTask(std::function<void()> func) {
    impl_->AddTask(func);
}

bool ThreadPool::Start() {
    return impl_->Start();
}

bool ThreadPool::Stop() {
    return impl_->Stop();
}

bool ThreadPool::IsAvailable() {
    return impl_->IsAvailable();
}

















