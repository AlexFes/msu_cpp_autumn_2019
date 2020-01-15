#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <queue>

class ThreadPool
{
private:
    bool flag;
    size_t size;
    std::vector<std::thread> threads;
	std::queue<std::function<void()>> taskQueue;

    // sync
    std::mutex m;
	std::condition_variable condvar;

	template <class Func, class... Args>
    void ExecFunc(std::promise<void> *promise, Func func, Args... args) {
        promise->set_value();
        delete promise;
        func(args...);
    }

    template <class Promise_ptr, class Func, class... Args>
    void ExecFunc(Promise_ptr promise, Func func, Args... args) {
        promise->set_value(func(args...));
        delete promise;
    }

public:
    explicit ThreadPool(size_t poolSize): size(poolSize), flag(true) {
    	for (size_t i = 0; i < size; ++i) {
    		threads.emplace_back(
    			[this]() {
    				while (flag) {
    					std::unique_lock<std::mutex> lock(m);

                        if (!taskQueue.empty()) {
    						auto task(std::move(taskQueue.front()));
    						taskQueue.pop();
    						lock.unlock();
    						task();
    					} else {
    						condvar.wait(lock);
    					}
    				}
    			}
    		);
    	}
    }

    ~ThreadPool() {
    	flag = false;
    	condvar.notify_all();

        for (size_t i = 0; i < size; ++i) {
    		threads[i].join();
    	}
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    	using promise_type = std::promise<decltype(func(args...))>;

    	auto promise = new promise_type();
    	auto res = promise->get_future();
    	auto t = [this](promise_type *promise, Func func, Args... args) {
            ExecFunc(promise, func, args...);
        };
        std::function<void()> task = std::bind(t, promise, func, args...);

        m.lock();
        taskQueue.push(task);
        m.unlock();

        condvar.notify_one();
        return res;
    }
};
