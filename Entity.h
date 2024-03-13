//
// Created by zthacker on 3/13/2024.
//

#ifndef BATTLE_ENTITY_H
#define BATTLE_ENTITY_H

#include <iostream>

using namespace std;

class Entity {
public:
    Entity(string n, int h, int m, int atk, int def, int magAtk, int magDef, int agl, int speed);
    ~Entity();
    string name;
    int hp;
    int mp;
    int attack;
    int defense;
    int magicAttack;
    int magicDefense;
    int agility;
    int speed;
    int timer;

    bool isAlive() const {
        return this->hp > 0;
    }

    void resetTimer() {
        this->timer = 1000 / speed;
    }
};


#endif //BATTLE_ENTITY_H
