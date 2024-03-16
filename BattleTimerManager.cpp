//
// Created by zthacker on 3/15/2024.
//

#include "BattleTimerManager.h"

#include <utility>

BattleTimerManager::BattleTimerManager() {
    this->m_running = false;
}

BattleTimerManager::~BattleTimerManager() {
    stopBattleTimerManager();
}

void BattleTimerManager::addTimer(Entity entity, function<void()> callBack) {
    lock_guard<mutex> lock(m_mutex);
    //another IDE change im not sure why -- Parameter 'callBack' is passed by value and only copied once; consider moving it to avoid unnecessary copies
    m_mapTimers[entity.id] = new Timer(seconds(1000/entity.speed),std::move(callBack));
    if(m_running) {
        m_mapTimers[entity.id]->start();
    }
}

void BattleTimerManager::startBattleTimeManager() {
    if(!m_running) {
        m_running = true;
        for(auto& [entityID, timer] : m_mapTimers) {
            timer->start();
        }
    }
}

void BattleTimerManager::stopBattleTimerManager() {
    if(m_running) {
        m_running = false;
        for(auto& [entityID, timer] : m_mapTimers) {
            timer->stop();
        }
    }
}

void BattleTimerManager::pauseAll() {
    for(auto& [entityID, timer] : m_mapTimers) {
        timer->pause();
    }
}

void BattleTimerManager::resumeAll() {
    for(auto& [entityID, timer] : m_mapTimers) {
        timer->resume();
    }
}
//my IDE had me make these const and I'm not sure why
//the parameter 'entity' is copied for each invocation but only used as a const reference; consider making it a const reference
void BattleTimerManager::stopTimer(const Entity& entity) {
    m_mapTimers[entity.id]->stop();
}

void BattleTimerManager::startTimer(const Entity& entity) {
    m_mapTimers[entity.id]->start();
}

void BattleTimerManager::pauseTimer(const Entity& entity) {
    m_mapTimers[entity.id]->pause();
}

void BattleTimerManager::resumeTimer(const Entity& entity) {
    m_mapTimers[entity.id]->resume();
}
