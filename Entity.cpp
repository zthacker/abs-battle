//
// Created by zthacker on 3/13/2024.
//

#include "Entity.h"

Entity::Entity(string n, int h, int m, int atk, int def, int magAtk, int magDef, int agl, int spd) {
    this->name = n;
    this->hp = h;
    this->mp = m;
    this->attack = atk;
    this->defense = def;
    this->magicAttack = magAtk;
    this->magicDefense = magDef;
    this->agility = agl;
    this->speed = spd;
    timer = 0;
}

Entity::~Entity() {

}
