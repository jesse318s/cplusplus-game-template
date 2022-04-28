#ifndef TERRAIN_H
#define TERRAIN_H
#include "globals.h"

using namespace std;

class Terrain {
public:
    SDL_Texture * texture;
    SDL_Rect rectangle;
    V2d<double> position;
    Terrain(SDL_Texture *);
    virtual ~Terrain();
    void draw();
};

#endif /* TERRAIN_H */

