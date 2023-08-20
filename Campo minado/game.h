#ifndef GAME_H
#define GAME_H

#include "tabuleiro.h"
#include "imagens.h"
#include <math.h>
#include <stdbool.h>

typedef struct
{
	bool restartGame;
	bool gameOver;
	int size;
	int nOfCells;
	int nOfBombs;
	int openCells;
	int notOpenCells;

}Game;

void mouseClick(int posX, int posY, int qtdCelulas, Board** campo, Uint8 button);

#endif
