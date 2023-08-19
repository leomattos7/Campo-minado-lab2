#ifndef IMAGENS_H
#define IMAGENS_H

#include <SDL.h>
#include <stdio.h>

typedef struct
{
    SDL_Texture* tabuleiro;
    SDL_Texture* celula;
    SDL_Texture* bomba;
    SDL_Texture* bandeira;
    SDL_Texture* celulaAberta;
    SDL_Texture* score;
    SDL_Texture* numeros[5];
}Textures;

void loadTextures(SDL_Renderer* renderer, Textures& textures);

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);

void setBack(int x, int y, SDL_Renderer* renderer, SDL_Texture* image);

void loadImage(int x, int y, int sizeX, int sizeY,
    SDL_Renderer* renderer, SDL_Texture* image);

#endif 