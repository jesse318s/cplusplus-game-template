#include "Terrain.h"

Terrain::Terrain(SDL_Texture * tex) {
    texture = tex;
    rectangle.w = 32;
    rectangle.h = 32;
}

Terrain::~Terrain() {
}

void Terrain::draw() {
    SDL_RenderCopy(ren, texture, NULL, &rectangle);
}

