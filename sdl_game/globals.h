#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_mixer.h>

#define WIDTH 1280
#define HIGHT 720

extern SDL_Renderer * ren;
extern SDL_Window * win;
extern double delta;
extern double time2;

using namespace std;

static int init = SDL_Init(SDL_INIT_EVERYTHING);
static int init2 = Mix_Init(0);
static auto key = SDL_GetKeyboardState(0);

template<typename T>
class V2d {
public:
    T x;
    T y;

    V2d<T> operator+=(const V2d<T>);
    V2d<T> operator*(double mult);
};

template<typename T>
V2d<T> V2d<T>::operator+=(const V2d<T> vec) {
    this->x += vec.x;
    this->y += vec.y;

    return *this;
}

template<typename T>
V2d<T> V2d<T>::operator*(double mult) {
    V2d<T> resultV;

    resultV.x = this->x * mult;
    resultV.y = this->y * mult;

    return resultV;
}

struct SaveData {
    float newHealthPoints;
    V2d<double> newPosition;
    V2d<double> newEnemyPosition;
    double potionPositionsXs[5];
    double potionPositionsYs[5];
    int potionCount;

    SaveData(float healthPoints, V2d<double> position, V2d<double> enemyPosition, double potionXs[5], double potionYs[5], int newPotionCount) {
        newHealthPoints = healthPoints;
        newPosition = position;
        newEnemyPosition = enemyPosition;

        for (int x = 0; x < 5; x++) {
            potionPositionsXs[x] = potionXs[x];
            potionPositionsYs[x] = potionYs[x];
        }
        
        potionCount = newPotionCount;
    }
};

#endif /* GLOBALS_H */

