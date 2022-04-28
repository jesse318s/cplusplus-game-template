#include "Player.h"

Player::Player() {
    flip = SDL_FLIP_NONE;
    speed = 300;
    texture = IMG_LoadTexture(ren, "spriteSheetPlayer.png");
    rectangle.x = 64;
    rectangle.y = 64;
    rectangle.w = 64;
    rectangle.h = 64;
    position.x = rectangle.x;
    position.y = rectangle.y;
    maxHP = 100;
    healthPoints = maxHP;
    hurtTime = 1;
    hurtTimer = hurtTime;

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
    //firing animations
    selection.x = 0;
    selection.y = 256;
    selection.w = 64;
    selection.h = 64;
    animations.push_back(new Animation(texture, selection, 8, .1));
    selection.x = 0;
    selection.y = 384;
    selection.w = 64;
    selection.h = 64;
    animations.push_back(new Animation(texture, selection, 8, .1));
    selection.x = 0;
    selection.y = 448;
    selection.w = 64;
    selection.h = 64;
    animations.push_back(new Animation(texture, selection, 8, .1));
    //set starting animation
    currentAnimation = animations[WALKDOWN];

    //set attack time
    attackTime = .2;
    // push back projectiles on to vector
    for (int x = 0; x < 13; x++) {
        fireballs.push_back(new Projectile());
    }
}

Player::~Player() {
    for (int x = 0; x < animations.size(); x++) {
        delete animations[x];
    }
}

void Player::update(Mouse * mouse) {
    //check for no save
    if (!((key[SDL_SCANCODE_LCTRL] || key[SDL_SCANCODE_RCTRL]) && key[SDL_SCANCODE_S])) {
        //read WASD keys
        if (key[SDL_SCANCODE_W]) {
            velocity = V2d<double>();
            velocity.y = -speed;
            position += velocity * delta;
            currentAnimation = animations[WALKUP];
            currentAnimation->animate();
        }
        if (key[SDL_SCANCODE_A]) {
            velocity = V2d<double>();
            velocity.x = -speed;
            position += velocity * delta;
            flip = SDL_FLIP_HORIZONTAL;
            currentAnimation = animations[WALKRIGHT];
            currentAnimation->animate();
        }
        if (key[SDL_SCANCODE_S]) {
            velocity = V2d<double>();
            velocity.y = +speed;
            position += velocity * delta;
            currentAnimation = animations[WALKDOWN];
            currentAnimation->animate();
        }
        if (key[SDL_SCANCODE_D]) {
            velocity = V2d<double>();
            velocity.x = +speed;
            position += velocity * delta;
            flip = SDL_FLIP_NONE;
            currentAnimation = animations[WALKRIGHT];
            currentAnimation->animate();
        }
    }

    rectangle.x = position.x;
    rectangle.y = position.y;

    //update active projectiles
    for (int x = 0; x < fireballs.size(); x++) {
        if (fireballs[x]->isActive) {
            fireballs[x]->update();
        }
    }

    //call attack on mouse click if timer hasn't expired
    if (SDL_GetMouseState(0, 0) != 0) {
        if (attackTimer < 0) {
            attack(mouse);
            attackTimer = attackTime;
        }

        //use previous animation to determine current firing animation
        Animation * previousAnimation = currentAnimation;

        if (currentAnimation == animations[WALKUP] || currentAnimation == animations[FIREUP]) {
            currentAnimation = animations[FIREUP];
            currentAnimation->animate();
        }
        if (currentAnimation == animations[WALKDOWN] || currentAnimation == animations[FIREDOWN]) {
            currentAnimation = animations[FIREDOWN];
            currentAnimation->animate();
        }
        if (currentAnimation == animations[WALKRIGHT] || currentAnimation == animations[FIRERIGHT]) {
            currentAnimation = animations[FIRERIGHT];
            currentAnimation->animate();
        }

        //reset animation to previous walking animation
        if (SDL_GetMouseState(0, 0) == 0) {
            currentAnimation = previousAnimation;
        }

    }

    attackTimer -= delta;

    //check to reset animation
    if (currentAnimation->isComplete) {
        currentAnimation->reset();
    }
}

void Player::draw() {
    SDL_RenderCopyEx(ren, texture, &currentAnimation->rect, &rectangle, NULL, NULL, flip);
}

void Player::attack(Mouse * mouse) {
    //establish and play sound effect
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Chunk * sound = Mix_LoadWAV("audio/fireball.wav");
    Mix_PlayChannel(-1, sound, 0);

    //calculate player/mouse angle
    double angleY = position.y - mouse->point.y;
    double angleX = mouse->point.x - position.x;
    double angle = atan2(angleY, angleX);

    //find inactive projectile and fire it
    for (int x = 0; x < fireballs.size(); x++) {
        if (!fireballs[x]->isActive) {
            fireballs[x]->flightTimer = 0;
            fireballs[x]->isActive = true;
            fireballs[x]->pos.x = position.x;
            fireballs[x]->pos.y = position.y;
            fireballs[x]->vel.x = cos(angle) * fireballs[x]->speed;
            fireballs[x]->vel.y = -sin(angle) * fireballs[x]->speed;
            return;
        }
    }
}
