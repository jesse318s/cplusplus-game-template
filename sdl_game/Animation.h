#pragma once
#include <vector>
#include "globals.h"
#include "Mouse.h"

using namespace std;

class Animation {
public:
    vector<double> frameTime; // should between 0.01 and .1 for most animations - lower is faster
    double frameTimer; // keeps track of how long a frame has been displayed
    int numberOfFrames; // total number of frames in the animation
    int x, y; // starting x and y values for an animation, top left corner of the rectangle
    SDL_Rect rect; // the source rectangle on the sprite sheet
    SDL_Texture *tex; // the image
    int frameCounter; // keeps track of which frame the animation is on
    bool isComplete = false; // a flag to know when the last frame is played

    Animation();
    // Receives the sprite sheet, starting place, num of frames, time each from should be played (can be adjusted per frame)
    Animation(SDL_Texture *, SDL_Rect startingRect, int numberOfFrames, double frameTime);
    ~Animation();

    // plays the animations
    void animate();

    // resets an animation to the first frame
    void reset();
};
