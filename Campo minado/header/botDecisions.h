#ifndef BOTDECISIONS_H
#define BOTDECISIONS_H

#include "game.h"
	
typedef struct
{
	int row;
	int col;
}CellBot;

void playing(Board** board, Game* game);

#endif