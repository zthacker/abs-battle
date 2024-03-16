//
// Created by zthacker on 3/13/2024.
//

#include "Entity.h"

Entity::Entity(int id, string n, int h, int m, int atk, int def, int magAtk, int magDef, int agl, int spd, int entityType) {
    id = id;
    name = n;
    hp = h;
    mp = m;
    attack = atk;
    defense = def;
    magicAttack = magAtk;
    magicDefense = magDef;
    agility = agl;
    speed = spd;
    entityType = entityType;
}

Entity::~Entity() {

}
