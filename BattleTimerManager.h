//
// Created by zthacker on 3/15/2024.
//

#ifndef BATTLE_BATTLETIMERMANAGER_H
#define BATTLE_BATTLETIMERMANAGER_H

#include <iostream>
#include <chrono>
#include <vector>
#include <mutex>
#include <map>
#include "Timer.h"
#include "Entity.h"

using namespace std;
using namespace chrono;

class BattleTimerManager {
public:
    BattleTimerManager();
    ~BattleTimerManager();

    void addTimer(Entity entity, function<void()> callBack);
    void startBattleTimeManager();
    void stopBattleTimerManager();
    void pauseAll();
    void resumeAll();
    void stopTimer(const Entity& entity);
    void startTimer(const Entity& entity);
    void pauseTimer(const Entity& entity);
    void resumeTimer(const Entity& entity);

private:
    vector<Timer*> m_timers;
    map<int, Timer*> m_mapTimers;
    bool m_running;
    mutex m_mutex;
};


#endif //BATTLE_BATTLETIMERMANAGER_H
