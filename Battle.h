//
// Created by zthacker on 3/13/2024.
//

#ifndef BATTLE_BATTLE_H
#define BATTLE_BATTLE_H

#include "Entity.h"
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
    BATTLE_STATE_TURN_AVAILABLE,
    BATTLE_STATE_BATTLE_OVER

} BATTLE_STATE;

enum
{
    BATTLE_RESULT_PLAYER_WIN,
    BATTLE_RESULT_ENEMY_WIN,
    BATTLE_RESULT_STREAM_CLOSED
}BATTLE_RESULT;

struct CompareSpeedStat {
    bool operator()(const Entity* e1, const Entity* e2) const {
        return e1->speed > e2->speed;
    }
};

class Battle {
public:
    Battle(vector<Entity*>* party, vector<Entity*>* enemies);
    ~Battle();
    void BattleStart();
    void Initialize();

private:
    void SetupBattle();
    vector<Entity*>* m_enemies;
    vector<Entity*>* m_party;
    vector<Entity*>* m_allPlayerAndEnemyEntities;
    int m_result;
    int m_state;

    priority_queue<Entity*, vector<Entity*>, CompareSpeedStat>* turnQueue;
};


#endif //BATTLE_BATTLE_H