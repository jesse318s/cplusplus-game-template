#ifndef ENEMY_H
#define ENEMY_H
#include <vector>
#include "globals.h"
#include "Animation.h"

using namespace std;

class Enemy {
public:
    V2d<double> position;
    V2d<double> velocity;
    V2d<double> target;
    vector<V2d<double>> patrolPoint;
    double speed;
    SDL_Texture * texture;
    SDL_Rect rectangle;
    SDL_RendererFlip flip;
    vector<Animation*> animations;
    Animation * currentAnimation;

    enum AnimationEnums {
        WALKUP, WALKDOWN, WALKRIGHT, DIE
    };
    Enemy();
    virtual ~Enemy();
    void update();
    void draw();
};

#endif /* ENEMY_H */

