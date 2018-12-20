#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <atomic>
#include <thread>
#include <future>
#include <condition_variable>
#include <iostream>


namespace bsl::thread {

using namespace std::chrono;

class Runnable {
protected:
    std::promise<void>	exitSignal;
    std::future<void>	futureObject;

    std::atomic<bool>	state = false;

public:
    virtual ~Runnable() = default;
    Runnable() :futureObject(exitSignal.get_future()) {}
    Runnable(Runnable && obj) : exitSignal(std::move(obj.exitSignal)), futureObject(std::move(obj.futureObject)) {
        std::cout << "Move Constructor called" << std::endl;
    }
    Runnable & operator=(Runnable && obj) {
        std::cout << "Move assignment is called" << std::endl;
        exitSignal = std::move(obj.exitSignal);
        futureObject = std::move(obj.futureObject);
        return *this;
    }

    // les classes enfants doivent donn� une d�finition
    virtual void run_service() = 0;

    // La fonction thread a executer
    std::thread start() {
        return std::thread([this] { this->run_service(); });
    }

    bool stopRequested() const
    {
        return !(futureObject.wait_for(0ms) == std::future_status::timeout);
    }

    virtual void stop() {
        exitSignal.set_value();
    }

    bool isRunning()
    {
        return state;
    }

};

}


#endif