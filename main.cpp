#include <iostream>

#include <iostream>
#include "Entity.h"
#include "Battle.h"

using namespace std;

int main() {

    //Pointer entities because I want them around later
    Entity* character1 = new Entity(0,"Character1", 300, 50, 60, 40, 20, 30, 100, 500, 0);
    Entity* character2 = new Entity(1,"Character2", 200, 50, 60, 40, 20, 30, 80, 400,0);

    //Non-pointer entities because I want them deleted when the scope is done
    Entity mob1 = Entity(2,"Mob1", 100, 50, 60, 40, 20, 30, 30, 300,1);
    Entity mob2 = Entity(3,"Mob2", 100, 50, 60, 40, 20, 30, 90, 200,1);

    //party will be a pointer, because we want that to be around also
    vector<Entity*>* party = new vector<Entity*>{character1, character2};

    //non pointer, since we want them removed after the battle scope
    vector<Entity> enemies{mob1, mob2};

    Battle battle = Battle(party, enemies);
    battle.BattleStart();

    return 0;
}
