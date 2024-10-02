#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>

class Timer {
	std::atomic<bool> active{true};
	
    public:
        void setTimeout(auto function, int delay);
        void setInterval(std::function<void()> function, int interval);
        void stopTimer();

};


