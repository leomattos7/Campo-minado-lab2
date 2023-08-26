#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <SDL.h>
#include "imagens.h"
#include <time.h>
#include <iostream>

#define POS_INI_X 400
#define POS_INI_Y 330
#define CELL_SIZE 30

typedef struct
{
    int isBomb;
    int isFlag;
    int nearbyBombs;
    int isOpen;
    int selected;

    int color;

    int posX;
    int posY;
}Board;

typedef struct
{
    int plusPositionX;
    int plusPositionY;

    int restartPositionX;
    int restartPositionY;
}Items;

Board** memoryAlloc(int size);


void aditionalItemsPos(Items* items);

void setAditionalItems(SDL_Renderer* renderer, Textures* texture, Items items);

void setBoard(int qtdCelulas, SDL_Renderer* renderer, const Textures* textures, Board** tabuleiro);

void nearbyBombs(int numbOfCells, Board** board);

void setNumbers(int qtdCelulas, SDL_Renderer* renderer, const Textures* textures, Board** tabuleiro);

#endif 
