#include "Enemy.h"

Enemy::Enemy() {
    flip = SDL_FLIP_NONE;
    speed = 300;
    texture = IMG_LoadTexture(ren, "spriteSheetEnemy.png");
    rectangle.x = 1152;
    rectangle.y = 64;
    rectangle.w = 64;
    rectangle.h = 64;
    position.x = rectangle.x;
    position.y = rectangle.y;

    //create animations
    SDL_Rect selection;
    selection.x = 0;
    selection.y = 512;
    selection.w = 64;
    selection.h = 64;
    animations.push_back(new Animation(texture, selection, 9, .1));
    selection.x = 0;
    selection.y = 640;
    selection.w = 64;
    selection.h = 64;
    animations.push_back(new Animation(texture, selection, 9, .1));
    selection.x = 0;
    selection.y = 704;
    selection.w = 64;
    selection.h = 64;
    animations.push_back(new Animation(texture, selection, 9, .1));
    selection.x = 0;
    selection.y = 1280;
    selection.w = 64;
    selection.h = 64;
    animations.push_back(new Animation(texture, selection, 6, .1));
    currentAnimation = animations[WALKDOWN];

    V2d<double> pos1;
    patrolPoint.push_back(pos1);
    patrolPoint[0].x = 1152;
    patrolPoint[0].y = 64;
    V2d<double> pos2;
    patrolPoint.push_back(pos2);
    patrolPoint[1].x = 640;
    patrolPoint[1].y = 64;

    target = patrolPoint[1];
}

Enemy::~Enemy() {
    for (int x = 0; x < animations.size(); x++) {
        delete animations[x];
    }
}

void Enemy::update() {
    //patrol area and animate
    if (target.x == patrolPoint[0].x) {
        velocity.x = +speed;
        position.x += velocity.x * delta;
        flip = SDL_FLIP_NONE;
        currentAnimation = animations[WALKRIGHT];
        currentAnimation->animate();
    }
    if (target.x == patrolPoint[1].x) {
        velocity.x = -speed;
        position.x += velocity.x * delta;
        flip = SDL_FLIP_HORIZONTAL;
        currentAnimation = animations[WALKRIGHT];
        currentAnimation->animate();
    }
    if (rectangle.x == patrolPoint[1].x) {
        target = patrolPoint[0];
    }
    if (rectangle.x == patrolPoint[0].x) {
        target = patrolPoint[1];
    }
    if (currentAnimation->isComplete) {
        currentAnimation->reset();
    }

    rectangle.x = position.x;
    rectangle.y = position.y;
}

void Enemy::draw() {
    SDL_RenderCopyEx(ren, texture, &currentAnimation->rect, &rectangle, NULL, NULL, flip);
}

