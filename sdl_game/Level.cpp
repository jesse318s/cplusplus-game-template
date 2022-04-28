#include "Level.h"

Level::Level() {
    //push new terrain and new pickup objects onto vector and list
    for (int x = 0; x < 10; x++) {
        int obsChance = rand() % 100 + 0;
        if (obsChance < 50) {
            obstacles.push_back(new Terrain(IMG_LoadTexture(ren, "terrain1.png")));
        }
        if (obsChance >= 50) {
            obstacles.push_back(new Terrain(IMG_LoadTexture(ren, "terrain2.png")));
        }
        obstacles[x]->rectangle.x = rand() % 1280 + 0;
        obstacles[x]->rectangle.y = rand() % 720 + 0;
    }
    for (int x = 0; x < 5; x++) {
        potions.push_back(new Pickup());
    }
    //declare player and enemy
    Player player;
    Enemy enemy;

    //declare load time
    loadTime = 5;
}

Level::~Level() {
}

void Level::checkCollision() {
    //check for potion/player intersection
    list<Pickup*>::iterator itr;
    for (itr = potions.begin(); itr != potions.end(); ++itr) {
        Pickup * potion = *itr;
        if (SDL_HasIntersection(&player.rectangle, &potion->destinationRectangle) && player.healthPoints < player.maxHP) {
            player.healthPoints += 10;
            potions.erase(itr);
            delete potion;
        }
    }
    //decrement hurt timer and check for player/enemy collision
    player.hurtTimer -= delta;
    if (SDL_HasIntersection(&player.rectangle, &enemy.rectangle) && player.hurtTimer <= 0) {
        player.healthPoints -= 10;
        player.hurtTimer = player.hurtTime;
    }
}

void Level::save() {
    //create save data
    int newPotionCount = 0;
    double potionXs[5];
    double potionYs[5];
    list<Pickup*>::iterator itr;
    for (itr = potions.begin(); itr != potions.end(); ++itr) {
        Pickup * potion = *itr;
        double x = potion->position.x;
        potionXs[newPotionCount] = x;
        double y = potion->position.y;
        potionYs[newPotionCount] = y;
        newPotionCount++;
    }
    SaveData saveData(player.healthPoints, player.position, enemy.position, potionXs, potionYs, newPotionCount);

    //create file stream and save data to file
    ofstream out("SaveData.dat", ios::out | ios::binary);
    out.write((char*) &saveData, sizeof (SaveData));
    out.close();
}

void Level::load() {
    //load save data
    int newPotionCount = 0;
    double potionXs[5];
    double potionYs[5];
    SaveData newData(player.healthPoints, player.position, enemy.position, potionXs, potionYs, newPotionCount);
    ifstream in("SaveData.dat", ios::in | ios::binary);
    if (in.is_open()) {
        in.read((char*) &newData, sizeof (SaveData));
        player.healthPoints = newData.newHealthPoints;
        player.position = newData.newPosition;
        enemy.position = newData.newEnemyPosition;
        list<Pickup*>::iterator itr;
        for (itr = potions.begin(); itr != potions.end(); ++itr) {
            Pickup * potion = *itr;
            potions.erase(itr);
            delete potion;
        }
        for (int x = 0; x < newData.potionCount; x++) {
            Pickup * potion = new Pickup(newData.potionPositionsXs[x], newData.potionPositionsYs[x]);
            potions.push_back(potion);
        }

        loadTimer = 5;
    }
    in.close();
}

void Level::enter() {

}

void Level::update() {

    while (true) {
        //set delta and time
        delta = (SDL_GetTicks() - time2) / 1000;
        time2 = SDL_GetTicks();

        //call update methods
        mouse.update();
        player.update(&mouse);
        enemy.update();
        list<Pickup*>::iterator itr;
        for (itr = potions.begin(); itr != potions.end(); ++itr) {
            Pickup * potion = *itr;
            potion->update();
        }

        checkCollision();

        //check for save
        if ((key[SDL_SCANCODE_LCTRL] || key[SDL_SCANCODE_RCTRL]) && key[SDL_SCANCODE_S]) {
            save();
        }

        //check for load
        loadTimer -= delta;
        if ((key[SDL_SCANCODE_LCTRL] || key[SDL_SCANCODE_RCTRL]) && key[SDL_SCANCODE_L] && loadTimer <= 0) {
            load();
        }

        //create health bar
        float healthBar = player.healthPoints;
        SDL_Rect healthFrame;
        healthFrame.x = 2;
        healthFrame.y = 2;
        healthFrame.w = 302;
        healthFrame.h = 66;
        SDL_Rect healthPoints;
        healthPoints.x = 3;
        healthPoints.y = 3;
        healthPoints.w = healthBar * 3;
        healthPoints.h = 64;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    exit(0);

            }

        }

        //draw background, objects, and mouse
        SDL_SetRenderDrawColor(ren, 50, 150, 50, 255);
        SDL_RenderClear(ren);
        for (int x = 0; x < obstacles.size(); x++) {
            obstacles[x]->draw();
        }
        list<Pickup*>::iterator itr2;
        for (itr2 = potions.begin(); itr2 != potions.end(); ++itr2) {
            Pickup * potion = *itr2;
            potion->draw();
        }
        enemy.draw();
        player.draw();
        for (int x = 0; x < player.fireballs.size(); x++) {
            if (player.fireballs[x]->isActive) {
                player.fireballs[x]->draw();
            }
        }
        mouse.draw();
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderDrawRect(ren, &healthFrame);
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &healthPoints);
        SDL_RenderPresent(ren);

    }// end main loop

}
