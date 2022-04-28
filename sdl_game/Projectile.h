#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "globals.h"

class Projectile {
public:
    SDL_Texture* texture;
    SDL_Rect rectangle;
    V2d<double> pos;
    V2d<double> vel;
    double speed;
    bool isActive;
    double flightTime;
    double flightTimer;
    Projectile();
    virtual ~Projectile();
    void update();
    void draw();
};

#endif /* PROJECTILE_H */

