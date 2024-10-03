#include "timercpp.h"

void Timer::setTimeout(auto function, int delay) {
    active = true;
    std::thread t([=, this]() {
        if(!active.load()) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(!active.load()) return;
        function();
    });
    t.detach();
}

void Timer::setInterval(std::function<void()> function, int interval) {
    active = true;
    std::thread t([=, this]() {
        while(active.load()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            if(!active.load()) return;
            function();
        }
    });
    t.detach();
}

void Timer::stopTimer() {
    active = false;
}