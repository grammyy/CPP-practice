#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template <typename T>
class ThreadQueue {
    private:
        std::queue<T> queue_;
        mutable std::mutex mutex_;
        std::condition_variable condition_;

    public:
        void enqueue(const T& item) {
            std::unique_lock<std::mutex> lock(mutex_);
            
            queue_.push(item);
            condition_.notify_one();
        }

        T dequeue() {
            std::unique_lock<std::mutex> lock(mutex_);
            condition_.wait(lock, [this] { return !queue_.empty(); });

            T item = queue_.front();

            queue_.pop();

            return item;
        }

        bool isEmpty() const {
            std::unique_lock<std::mutex> lock(mutex_);

            return queue_.empty();
        }
};

int main() {
    ThreadQueue<int> tsQueue;

    std::thread producer([&tsQueue]() {
        for (int i = 1; i <= 5; ++i) {
            tsQueue.enqueue(i);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    for (int i = 0; i < 5; ++i) {
        int item = tsQueue.dequeue();
        
        std::cout << "Dequeued: " << item << std::endl;
    }

    producer.join();

    return 0;
}