#include "globals.h"
#include "State.h"
#include "Mouse.h"
#include "Level.h"

// Initialize global externs
SDL_Window * win = SDL_CreateWindow("sdl_game-jesse", SDL_WINDOWPOS_UNDEFINED,
        10, WIDTH, HIGHT, NULL);
SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
double delta = .0001;
double time2 = SDL_GetTicks();

using namespace std;

// set static state members
State * State::level = new Level();
Mouse State::mouse = Mouse();

int main(int argc, char** argv) {

    //main loop
    while (true) {
        State::level->update();

    }

    return 0;
}


