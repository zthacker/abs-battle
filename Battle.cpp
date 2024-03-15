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

    //setup entities
    for(auto p : *m_party) {
        p->ready = false;
        p->batleTime = p->speed;
        m_allPlayerAndEnemyEntities->push_back(p);
    }
    for(auto e : *m_enemies) {
        e->ready = false;
        e->batleTime = e->speed;
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

                //getting a buggy interaction when all Entities have the same speed -- only 2 make it in
                //but only at the start
                for(auto e : *m_allPlayerAndEnemyEntities) {
                    if(!e->ready && clock()/CLOCKS_PER_SEC > 0 && clock()/CLOCKS_PER_SEC % e->batleTime == 0) {
                        e->ready = true;
                        cout << e->name << " has a battle timer of: " << e->batleTime << " and is going into queue at: " << clock() / CLOCKS_PER_SEC << endl;
                        //turnQueue is a priority_queue -- so "ties" of battleTime are deteremined by the AGI stat
                        turnQueue->push(e);
                    }

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
                    cout<<"It's "<<currentEntity->name <<"'s turn at second: "<<clock()/CLOCKS_PER_SEC<<endl;

                    //simulate a turn
                    cout<<"simulating a turn that takes 2 seconds"<<endl;
                    this_thread::sleep_for(milliseconds(2000));

                    //set the battle timer to be current clock in seconds plus the entities speed. Essentially, we're making the battleTime
                    //a point in time at which they will be considered for a turn.
                    currentEntity->batleTime = currentEntity->speed + clock() / CLOCKS_PER_SEC;
                    cout<<"Clock: "<<clock()/CLOCKS_PER_SEC<<endl;
                    cout<<"Speed: "<<currentEntity->speed<<endl;
                    cout << "BattleTimer: " << currentEntity->batleTime << endl;

                    //go back to being not ready
                    currentEntity->ready = false;
                }
                //change state back to waiting for turns once the turn queue is empty
                m_state = BATTLE_STATE_WAITING_FOR_TURN;
            }
            break;
        }
    }
}


