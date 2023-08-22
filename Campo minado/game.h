#ifndef GAME_H
#define GAME_H

#include "tabuleiro.h"
#include "imagens.h"
#include <iostream>

typedef struct
{
	bool restartGame;
	bool gameOver;
	
	int size;
	int realoca;
	int nOfBombs;
	int openCells;
	int notOpenCells;

}Game;

void mouseClick(int posX, int posY, Game* game, Board** board, Items item, Uint8 button);

#endif
