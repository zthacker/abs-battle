//
// Created by zthacker on 3/13/2024.
//

#ifndef BATTLE_BATTLE_H
#define BATTLE_BATTLE_H

#include "Entity.h"
#include "BattleTimerManager.h"
#include <vector>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

enum
{
    BATTLE_STATE_SETUP,
    BATTLE_STATE_ENEMY_TURN,
    BATTLE_STATE_PLAYER_TURN,
    BATTLE_STATE_WAITING_FOR_TURN,
    BATTLE_STATE_PERFORMING_ACTION,
    BATTLE_STATE_BATTLE_OVER

} BATTLE_STATE;

enum
{
    BATTLE_RESULT_PLAYER_WIN,
    BATTLE_RESULT_ENEMY_WIN,
    BATTLE_RESULT_STREAM_CLOSED
}BATTLE_RESULT;

struct CompareStat {
    bool operator()(const Entity e1, const Entity e2) const {
        return e1.agility > e2.agility;
    }
};

class Battle {
public:
    Battle(vector<Entity*>* party, vector<Entity> enemies);
    ~Battle();
    void BattleStart();
    void Initialize();

private:
    void SetupBattle();
    void cb_EntityReady(Entity entity);
    vector<Entity> m_enemies;
    vector<Entity*>* m_party;
    vector<Entity> m_allPlayerAndEnemyEntities;
    int m_result;
    int m_state;

    priority_queue<Entity, vector<Entity>, CompareStat> actionQueue;
    queue<Entity> readyQueue;
    BattleTimerManager m_battleTimerManager;

};


#endif //BATTLE_BATTLE_H