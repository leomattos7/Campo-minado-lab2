#ifndef GAME_H
#define GAME_H

#include "tabuleiro.h"
#include "imagens.h"
#include <iostream>

typedef struct
{
	bool restartGame;
	bool gameOver;
	int gameStart;

	int size;
	int reallocUp;
	int nOfBombs;
	int openCells;
	
	int menu;
	int gameMode;
}Game;

void initBoard(Board** board, int size, int* start);

void mouseClick(int posX, int posY, Game* game, Board** board, Items item, Uint8 button);

#endif
