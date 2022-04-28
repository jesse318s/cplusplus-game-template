#ifndef PICKUP_H
#define PICKUP_H
#include <cmath>
#include "globals.h"

using namespace std;

class Pickup {
public:
    V2d<double> position;
    SDL_Texture * texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    float angle;
    float bounceSpeed;
    float bounceHeight;
    Pickup();
    Pickup(int x, int y);
    virtual ~Pickup();
    void update();
    void draw();
};

#endif /* PICKUP_H */

