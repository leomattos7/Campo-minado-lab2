#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <SDL.h>
#include <stdio.h>
#include "imagens.h"
#include <time.h>
#include <stdlib.h>

#define POS_INI_X 400
#define POS_INI_Y 330
#define CELL_SIZE 30

typedef struct
{
    int isBomb;
    int isFlag;
    int neighborBombCount;
    int isOpen;

    int posX;
    int posY;
}Board;

Board** memoryAlloc(int tamanho);

void initBoard(Board** tabuleiro, int tamanho);

void setBoard(int qtdCelulas, SDL_Renderer* renderer, const Textures* textures, Board** tabuleiro);

void randomlyGenerateBombs(int qtdCelulas, Board** tabuleiro);

void setNumbers(int qtdCelulas, SDL_Renderer* renderer, const Textures* textures, Board** tabuleiro);

#endif 
