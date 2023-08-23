#ifndef IMAGENS_H
#define IMAGENS_H

#include <SDL.h>
#include <stdio.h>

typedef struct
{
    SDL_Texture* board;
    SDL_Texture* cell[2];
    SDL_Texture* bomb;
    SDL_Texture* redBomb;
    SDL_Texture* flag;
    SDL_Texture* openCell;
    SDL_Texture* score;
    SDL_Texture* numbers[5];

    SDL_Texture* plus;

    SDL_Texture* player;
    SDL_Texture* bot;
}Textures;

void loadTextures(SDL_Renderer* renderer, Textures& textures);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);

void setBack(int x, int y, SDL_Renderer* renderer, SDL_Texture* image);

void loadImage(int x, int y, int sizeX, int sizeY,
    SDL_Renderer* renderer, SDL_Texture* image);

#endif 