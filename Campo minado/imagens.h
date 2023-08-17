#ifndef IMAGENS_H
#define IMAGENS_H

#include <SDL.h>
#include <stdio.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);

void setBack(int x, int y, SDL_Renderer* renderer, SDL_Texture* image);

void setImgFree(int x1, int x2, int y1, int y2,
    SDL_Renderer* renderer, SDL_Texture* image);

void loadImage(int x, int y, int sizeX, int sizeY,
    SDL_Renderer* renderer, SDL_Texture* image);

#endif 