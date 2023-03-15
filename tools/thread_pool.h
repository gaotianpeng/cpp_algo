//
// Created by gtp on 2023/3/15.
//

#ifndef CPP_ALGO_THREAD_POOL_H
#define CPP_ALGO_THREAD_POOL_H

#include <functional>
#include <future>
#include <memory>

class ThreadPool {
public:
    explicit ThreadPool(int thread_num = 4);
    ~ThreadPool();

public:
    bool Start();
    bool Stop();

    template<typename F, typename... Args>
    auto Run(F&& f, Args&& ...args)
        -> std::shared_ptr<std::future<std::result_of_t<F(Args...)>>>;

private:
    void AddTask(std::function<void()> func);
    bool IsAvailable();

private:
    class Impl;
    std::shared_ptr<Impl> impl_;
};

template <typename F, typename... Args>
auto ThreadPool::Run(F &&f, Args &&... args) -> std::shared_ptr<std::future<std::result_of_t<F(Args...)>>> {
    if (!IsAvailable()) {
        return nullptr;
    }

    using return_type = std::result_of_t<F(Args...)>;
    auto task = std::make_shared<std::packaged_task<return_type()>>(
          std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    std::future<return_type> res = task->get_future();
    auto func = [task]() {
        (*task)();
    };
    AddTask(func);

    return std::make_shared<std::future<std::result_of_t<F(Args...)>>>(std::move(res));
}


#endif //CPP_ALGO_THREAD_POOL_H
