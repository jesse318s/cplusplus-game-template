#include "Pickup.h"

Pickup::Pickup() {
    angle = 0;
    texture = IMG_LoadTexture(ren, "pickup.png");
    bounceHeight = .01;
    bounceSpeed = 15;
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = 32;
    sourceRectangle.h = 32;
    destinationRectangle.w = sourceRectangle.w;
    destinationRectangle.h = sourceRectangle.h;

    //randomize pickup object placement
    int posChanceX = rand() % 1280 + 0;
    int posChanceY = rand() % 720 + 0;
    position.x = posChanceX;
    position.y = posChanceY;
    destinationRectangle.x = position.x;
    destinationRectangle.y = position.y;
}

Pickup::Pickup(int x, int y) {
    angle = 0;
    texture = IMG_LoadTexture(ren, "pickup.png");
    bounceHeight = .01;
    bounceSpeed = 15;
    sourceRectangle.x = 0;
    sourceRectangle.y = 0;
    sourceRectangle.w = 32;
    sourceRectangle.h = 32;
    destinationRectangle.w = sourceRectangle.w;
    destinationRectangle.h = sourceRectangle.h;
    position.x = x;
    position.y = y;
    destinationRectangle.x = position.x;
    destinationRectangle.y = position.y;
}

Pickup::~Pickup() {
}

void Pickup::update() {
    //update bounce position based on sin wave function and bounce height
    angle += bounceSpeed * delta;

    position.y += bounceHeight * sin(angle);

    destinationRectangle.y = position.y - destinationRectangle.h / 2;
}

void Pickup::draw() {
    SDL_RenderCopy(ren, texture, &sourceRectangle, &destinationRectangle);
}

