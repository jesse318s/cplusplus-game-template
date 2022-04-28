#include "Projectile.h"

Projectile::Projectile() {
    texture = IMG_LoadTexture(ren, "playerProjectile.png");
    speed = 400;
    isActive = false;
    flightTime = 2;
    rectangle.w = 32;
    rectangle.h = 32;
}

Projectile::~Projectile() {
}

void Projectile::update() {
    pos += vel * delta;
    rectangle.x = pos.x;
    rectangle.y = pos.y;

    flightTimer += delta;

    if (flightTimer > flightTime) {
        isActive = false;
    }
}

void Projectile::draw() {
    SDL_RenderCopy(ren, texture, NULL, &rectangle);
}
