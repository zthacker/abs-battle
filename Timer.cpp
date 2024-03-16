//
// Created by zthacker on 3/15/2024.
//

#include "Timer.h"

Timer::Timer(seconds millisecondInterval, function<void()> callBack) {
    m_millisecondInterval = millisecondInterval;
    m_callBack = callBack;
    m_active = false;
    m_paused = false;
}


Timer::~Timer() {
    stop();
}

void Timer::start() {
    if(!m_active) {
        m_active = true;
        m_thread = thread(&Timer::run, this);
    }
}

void Timer::stop() {
    if(m_active) {
        m_active = false;
        if(m_thread.joinable()) {
            cout<<"joinable"<<endl;
            m_thread.join();
        }
    }
}

void Timer::run() {
    while(m_active) {
        this_thread::sleep_for(m_millisecondInterval);
        if(!m_paused) {
            m_callBack();
        } else {
            unique_lock<mutex> lock(m_mutex);
            m_cv.wait(lock, [this]() {return !m_paused;});
        }
    }
}

void Timer::pause() {
    m_paused = true;
}

void Timer::resume() {
    m_paused = false;
    m_cv.notify_one();
}
