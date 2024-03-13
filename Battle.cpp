//
// Created by zthacker on 3/13/2024.
//

#include "Battle.h"
#include <thread>
#include <ctime>


Battle::Battle(vector<Entity*>* party, vector<Entity*>* enemies) {
    m_state = BATTLE_STATE_SETUP;
    this->m_party = party;
    this->m_enemies = enemies;
    this->m_allPlayerAndEnemyEntities = new vector<Entity*>;
    this->turnQueue = new priority_queue<Entity*, vector<Entity*>, CompareSpeedStat>;

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
    
    for(auto p : *m_party) {
        p->resetTimer();
        m_allPlayerAndEnemyEntities->push_back(p);
    }
    for(auto e : *m_enemies) {
        e->resetTimer();
        m_allPlayerAndEnemyEntities->push_back(e);
    }
    m_state = BATTLE_STATE_WAITING_FOR_TURN;
    
}

void Battle::BattleStart() {
    while (m_state != BATTLE_STATE_BATTLE_OVER) {
        switch (m_state) {
            case BATTLE_STATE_SETUP:
            {
                cout<<"BATTLE_STATE_SETUP\n";
                Initialize();
            }
            case BATTLE_STATE_WAITING_FOR_TURN:
            {
                //cout<<"BATTLE_STATE_WAITING_FOR_TURN\n";
                for(auto e : *m_allPlayerAndEnemyEntities) {
                    //since we're looping over all the entities, multiples can have timer 0.
                    //We want the speed stat to determine priority in the priority_queue
                    if(e->timer <= 0) {
                        turnQueue->push(e);
                    }
                    //decrement the timer
                    e->timer -= 1;
                }
                if(!turnQueue->empty()) {
                    m_state = BATTLE_STATE_TURN_AVAILABLE;
                }
            }
            break;
            case BATTLE_STATE_TURN_AVAILABLE:
            {
                //cout<<"BATTLE_STATE_TURN_AVAILABLE\n";
                while(!turnQueue->empty()) {
                    Entity* currentEntity = turnQueue->top();
                    turnQueue->pop();
                    cout<<"It's "<<currentEntity->name <<"'s turn."<< endl;
                    //here to simulate a turn
                    this_thread::sleep_for(milliseconds(500));
                    currentEntity->resetTimer();

                }
                //change state back to waiting for turns once the turn queue is empty
                m_state = BATTLE_STATE_WAITING_FOR_TURN;
            }
            break;
        }
    }
}


