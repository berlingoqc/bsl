#ifndef THREAD_H
#define THREAD_H

#include <mutex>
#include <atomic>
#include <thread>
#include <queue>
#include <chrono>
#include <future>
#include <condition_variable>
#include <iostream>


namespace bsl::thread {

template<typename dataType>
class ConcurrentQueue {
private:
    std::queue<dataType>	queue;
    std::mutex				mutex;

    std::condition_variable cv;

    std::atomic<bool>		forceExit = false;

public:

    dataType& pop();
    dataType pop2();

    dataType pop2_wait(std::chrono::milliseconds timeout, bool* has_data);

    dataType pop_wait(std::chrono::milliseconds timeout,bool* has_data);

    dataType* pop_all_wait(std::chrono::milliseconds timeout,int* nbrElement);

    void push(dataType const& data);

    void empty();

    bool isEmpty();
};
}
#endif //THREAD_H
