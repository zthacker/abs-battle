#include <iostream>

#include <iostream>
#include "Entity.h"
#include "Battle.h"

using namespace std;

int main() {

    Entity* character1 = new Entity("Character1", 300, 50, 60, 40, 20, 30, 50, 10);
    Entity* character2 = new Entity("Character2", 200, 50, 60, 40, 20, 30, 50, 15);
    Entity* mob1 = new Entity("Mob1", 100, 50, 60, 40, 20, 30, 50, 5);
    Entity* mob2 = new Entity("Mob2", 100, 50, 60, 40, 20, 30, 50, 1);

    vector<Entity*>* party = new vector<Entity*>;
    vector<Entity*>* enemies = new vector<Entity*>;

    party->push_back(character1);
    party->push_back(character2);

    enemies->push_back(mob1);
    enemies->push_back(mob2);

    Battle* battle = new Battle(party, enemies);
    battle->BattleStart();

    return 0;
}
