//
// Created by zthacker on 3/13/2024.
//

#include "Battle.h"
#include <thread>
#include <ctime>


Battle::Battle(vector<Entity*>* party, vector<Entity> enemies) {
    m_state = BATTLE_STATE_SETUP;
    m_enemies = enemies;
    this->m_party = party;

}

Battle::~Battle() {
    m_state = BATTLE_STATE_SETUP;
}

void Battle::Initialize() {
    cout<<"Initializing battle"<<endl;
    m_result = BATTLE_RESULT_STREAM_CLOSED;
    SetupBattle();
}

void Battle::SetupBattle() {

    cout<<"Setting up battle"<<endl;

    //setup entities
    for(auto p : *m_party) {
        m_battleTimerManager.addTimer(*p,[p, this](){ cb_EntityReady(*p);});
        m_allPlayerAndEnemyEntities.push_back(*p);
    }
    for(auto e : m_enemies) {
        m_battleTimerManager.addTimer(e, [this, e](){ cb_EntityReady(e);});
        m_allPlayerAndEnemyEntities.push_back(e);
    }
    cout<<"starting battle timer manager"<<endl;
    m_battleTimerManager.startBattleTimeManager();
    cout<<"changing state to waiting for turn"<<endl;
    m_state = BATTLE_STATE_WAITING_FOR_TURN;
    
}

void Battle::BattleStart() {
    while (m_state != BATTLE_STATE_BATTLE_OVER) {
        switch (m_state) {
            case BATTLE_STATE_SETUP: {
                cout << "BATTLE_STATE_SETUP\n";
                Initialize();
            }
            case BATTLE_STATE_WAITING_FOR_TURN: {
                while (!readyQueue.empty()) {
                    Entity ce = readyQueue.front();
                    readyQueue.pop();

                    cout << ce.name << " is performing an action! PewPew" << endl;
                    //pause all timers since we're going to be doing an action -- this is mimicing a "Wait" system
                    m_battleTimerManager.pauseAll();
                    //simulate an action
                    this_thread::sleep_for(milliseconds(1000));

                    //resume all timers
                    m_battleTimerManager.resumeAll();
                }
                break;
                case BATTLE_STATE_PERFORMING_ACTION: {
//                //cout<<"BATTLE_STATE_TURN_AVAILABLE\n";
                }
                break;
            }
        }
    }
}

//TODO Currently, I cant use m_battleTimerManager.stopTimer() on the Timer object. I get:
//terminate called after throwing an instance of 'std::system_error'
//what():  Resource deadlock avoided
//terminate called recursively
void Battle::cb_EntityReady(Entity entity) {
    cout << entity.name << " is ready for their turn!" << endl;
    m_battleTimerManager.pauseTimer(entity);
    readyQueue.push(entity);
}


