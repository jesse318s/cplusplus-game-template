#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <list>
#include <fstream>
#include "globals.h"
#include "State.h"
#include "Mouse.h"
#include "Player.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Terrain.h"

using namespace std;

class Level : public State {
public:
    Player player;
    Enemy enemy;
    vector<Terrain*> obstacles;
    list<Pickup*> potions;
    double loadTime;
    double loadTimer;
    
    Level();
    virtual ~Level();
    void checkCollision();
    void save();
    void load();
    void enter();
    void update();
};

#endif /* LEVEL_H */

