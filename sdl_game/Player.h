#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <cmath>
#include "globals.h"
#include "Mouse.h"
#include "Animation.h"
#include "Projectile.h"

using namespace std;

class Player {
public:
    V2d<double> position;
    V2d<double> velocity;
    double speed;
    SDL_Texture * texture;
    SDL_Rect rectangle;
    SDL_RendererFlip flip;
    vector<Animation*> animations;
    Animation * currentAnimation;
    vector<Projectile*> fireballs;
    double attackTimer;
    double attackTime;
    double hurtTimer;
    double hurtTime;
    float maxHP;
    float healthPoints;

    enum AnimationEnums {
        WALKUP, WALKDOWN, WALKRIGHT, DIE, FIREUP, FIREDOWN, FIRERIGHT
    };
    Player();
    virtual ~Player();
    void update(Mouse *);
    void draw();
    void attack(Mouse *);
};

#endif /* PLAYER_H */

