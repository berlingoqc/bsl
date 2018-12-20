#include "queue.h"


namespace bsl::thread {

template<typename dataType>
dataType& ConcurrentQueue<dataType>::pop()
{
    std::unique_lock<std::mutex> lk(mutex);
    cv.wait(lk, [this] { return !queue.empty(); }); // Attend que la queue ne soit plus vide et utiliser
    dataType& f = queue.front();
    queue.pop();
    return f;
}
template<typename dataType>
dataType ConcurrentQueue<dataType>::pop2() {
    std::unique_lock<std::mutex> lk(mutex);
    cv.wait(lk, [this] { return !queue.empty(); }); // Attend que la queue ne soit plus vide et utiliser
    dataType f = queue.front();
    queue.pop();
    return f;
}

template<typename dataType>
dataType ConcurrentQueue<dataType>::pop2_wait(std::chrono::milliseconds timeout, bool* has_data) {
    std::unique_lock<std::mutex> lk(mutex);
    if (!cv.wait_for(lk, timeout, [this] { return !queue.empty(); }))
    {
        *has_data = false;
        return dataType();
    }
    *has_data = true;
    dataType f = queue.front();
    queue.pop();
    return f;
}

template<typename dataType>
dataType ConcurrentQueue<dataType>::pop_wait(std::chrono::milliseconds timeout,bool* has_data)
{
    std::unique_lock<std::mutex> lk(mutex);
    if(!cv.wait_for(lk, timeout, [this] { return !queue.empty(); }))
    {
        *has_data = false;
        return dataType();
    }
    *has_data = true;
    dataType f = queue.front();
    queue.pop();
    return f;
}

template<typename dataType>
dataType* ConcurrentQueue<dataType>::pop_all_wait(std::chrono::milliseconds timeout,int* nbrElement)
{
    std::unique_lock<std::mutex> lk(mutex);
    if (!cv.wait_for(lk, timeout, [this] { return !queue.empty(); }))
    {
        *nbrElement = 0;
        return nullptr;
    }
    *nbrElement = queue.size();
    dataType* d = new dataType[*nbrElement];
    for(int i =0; i<*nbrElement;i++)
    {
        d[i] = queue.front();
        queue.pop();
    }
    return d;
}

template<typename dataType>
void ConcurrentQueue<dataType>::push(dataType const& data) {
    forceExit.store(false);
    std::unique_lock<std::mutex> lk(mutex);
    queue.push(data);
    lk.unlock();
    cv.notify_one();
}

template<typename dataType>
void ConcurrentQueue<dataType>::empty()
{
    std::unique_lock<std::mutex> lk(mutex);
    for(int i = 0; i < queue.size(); i++)
    {
        queue.pop();
    }
    lk.unlock();
}

template<typename dataType>
bool ConcurrentQueue<dataType>::isEmpty() {
    std::unique_lock<std::mutex> lk(mutex);
    return queue.empty();
}

}