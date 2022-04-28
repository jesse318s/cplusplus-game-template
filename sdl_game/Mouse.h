#ifndef MOUSE_H
#define MOUSE_H
#include "globals.h"

class Mouse {
public:
    SDL_Texture *tex;
    SDL_Rect rect;
    SDL_Rect point; // for collision detection
    void update();
    void draw();
    Mouse();
    virtual ~Mouse();
};

#endif /* MOUSE_H */

