#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>

class ThreadPool {
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        std::mutex queueMutex;
        std::mutex coutMutex;  // Added mutex for std::cout
        std::condition_variable condition;
        bool stop;

    public:
        ThreadPool(size_t numThreads) : stop(false) {
            for (size_t i = 0; i < numThreads; ++i) {
                workers.emplace_back([this] {
                    while (true) {
                        std::function<void()> task;

                        {
                            std::unique_lock<std::mutex> lock(queueMutex);
                            condition.wait(lock, [this] { return stop || !tasks.empty(); });

                            if (stop && tasks.empty()) {
                                return;
                            }

                            task = std::move(tasks.front());
                            tasks.pop();
                        }

                        task();
                    }
                });
            }
        }

        ~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(queueMutex);
                stop = true;
            }

            condition.notify_all();

            for (std::thread& worker : workers) {
                worker.join();
            }
        }

        template <class F, class... Args>
        auto addTask(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
            using return_type = decltype(f(args...));

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            {
                std::unique_lock<std::mutex> lock(queueMutex);
                tasks.emplace([task]() {
                    (*task)();
                });
            }

            condition.notify_one();

            return task->get_future();
        }
};

// Helper function to simulate work
void simulateWork(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main() {
    ThreadPool threadPool(4);
    std::vector<std::future<std::string>> futures;

    for (int i = 0; i < 10; ++i) {
        futures.emplace_back(threadPool.addTask([i]() -> std::string {
            simulateWork(100); // Simulating some work
            
            return "Task " + std::to_string(i) + " executed by thread " + std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));
        }));
    }

    for (auto& future : futures) {
        future.wait();
    }

    std::vector<std::string> results;
    for (auto& future : futures) {
        results.push_back(future.get());
    }

    // Barrier to wait for all tasks to complete
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // Print all thread results
    for (const auto& result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}
