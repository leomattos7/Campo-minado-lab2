#ifndef GAME_H
#define GAME_H

#include "tabuleiro.h"
#include "imagens.h"
#include <SDL.h>
#include <ctime>
#include <iostream>
#include <thread>
#include <chrono>
#include <list>

using namespace std;

typedef struct
{
	int restartGame;
	int gameOver;
	int gameStart;

	int size;
	int reallocUp;
	int nOfBombs;
	int openCells;
	int running;
	
	int menu;
	int gameMode;
}Game;

void initGame(Game* game);

void updateBot(Game* game, SDL_Renderer* renderer, const Textures* textures, Board** board);

void setInitialTextures(SDL_Renderer* renderer, Textures* textures, Items items);

void deleteBoard(Board** board, int size);

void reallocBoard(Game* game, Board*** board);

void events(SDL_Event event, Game* game, Board** board, Items item);

void update(Game* game, SDL_Renderer* renderer, Textures* textures, Board** board);

void dispose(SDL_Renderer** renderer, SDL_Window** window);

void initBoard(Board** board, int size);

void mouseClick(int posX, int posY, Game* game, Board** board, Items item, Uint8 button);

void playCell(Board** board, Game* game, int row, int col, int button);

#endif
