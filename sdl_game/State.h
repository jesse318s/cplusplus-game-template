#ifndef STATE_H
#define STATE_H
#include "globals.h"
#include "Mouse.h"

class State {
public:
    static State * level;
    static Mouse mouse;
    SDL_Texture * background = nullptr;
    State();
    virtual ~State();
    virtual void enter() = 0;
    virtual void update() = 0;
};

#endif /* STATES_H */

