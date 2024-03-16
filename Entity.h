//
// Created by zthacker on 3/13/2024.
//

#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include <iostream>
#include "Timer.h"

using namespace std;

enum
{
    PLAYER, // 0
    ENEMY // 1
}ENTITY_TYPE;

class Entity {
public:
    Entity(int id, string n, int h, int m, int atk, int def, int magAtk, int magDef, int agl, int speed, int entityType);
    ~Entity();
    int id;
    string name;
    int hp;
    int mp;
    int attack;
    int defense;
    int magicAttack;
    int magicDefense;
    int agility;
    int speed;
    int batleTime;
    bool ready;
    int entityType;

    bool isAlive() const {
        return this->hp > 0;
    }


};


#endif //BATTLE_ENTITY_H
