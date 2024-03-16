//
// Created by zthacker on 3/15/2024.
//

#ifndef BATTLE_TIMER_H
#define BATTLE_TIMER_H


#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
#include <condition_variable>

using namespace std;
using namespace chrono;

class Timer {
public:
    Timer(seconds millisecondInterval, function<void()> callBack);
    ~Timer();

    void start();
    void stop();
    void pause();
    void resume();


private:
    void run();
    milliseconds m_millisecondInterval;
    function<void()> m_callBack;
    thread m_thread;
    bool m_active;
    bool m_paused;
    condition_variable m_cv;
    mutex m_mutex;

};


#endif //BATTLE_TIMER_H
