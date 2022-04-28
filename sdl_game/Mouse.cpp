#include "Mouse.h"

Mouse::Mouse() {
    tex = IMG_LoadTexture(ren, "mouse.png");
    rect.x = 0;
    rect.y = 0;
    rect.w = 25;
    rect.h = 25;

    point.h = point.w = 1; // collision rectangle should only be 1 pixel
    SDL_ShowCursor(false); // hide the OS's mouse
}

Mouse::~Mouse() {
    SDL_DestroyTexture(tex);
}

void Mouse::update() {
    SDL_GetMouseState(&rect.x, &rect.y);
    point.x = rect.x;
    point.y = rect.y;
}

void Mouse::draw() {
    SDL_RenderCopy(ren, tex, NULL, &rect);
}

