#ifndef GAME_H
#define GAME_H

#include "tabuleiro.h"
#include "imagens.h"
#include <iostream>

typedef struct
{
	int restartGame;
	int gameOver;
	int gameStart;

	int size;
	int reallocUp;
	int nOfBombs;
	int openCells;
	
	int menu;
	int gameMode;
}Game;

void initGame(Game* game);

void events(SDL_Event event, Game* game, Board** board, Items item);

void update(Game* game, SDL_Renderer* renderer, Textures* textures, Board** board);

void initBoard(Board** board, int size, int* start);

void mouseClick(int posX, int posY, Game* game, Board** board, Items item, Uint8 button);

#endif
