#include "game.h"

static int mouseCellIntersection(int posX, int posY, int qtdCelulas)
{
	int xIni = POS_INI_X - (qtdCelulas * (CELL_SIZE / 2));
	int xFim = POS_INI_X + (qtdCelulas * (CELL_SIZE / 2));
	int yIni = POS_INI_Y - (qtdCelulas * (CELL_SIZE / 2));
	int yFim = POS_INI_Y + (qtdCelulas * (CELL_SIZE / 2));
	if(posX >= xIni && posX <= xFim && posY >= yIni && posY <= yFim)
		return 1;
	return 0;
}

static void getPos(int posX, int posY, int qtdCelulas, int* linha, int* coluna, Board** campo)
{
	for(int i = 0; i < qtdCelulas; i++)
		for(int j = 0; j < qtdCelulas; j++)
			if (posX >= campo[i][j].posX && posX <= campo[i][j].posX + CELL_SIZE &&
				posY >= campo[i][j].posY && posY <= campo[i][j].posY + CELL_SIZE)
			{
				*linha = i;
				*coluna = j;
				return;
			}
}

static void revealCells(int line, int column, Board** board, int numberOfCells)
{
	if (line < 0 || line >= numberOfCells || column < 0 || column >= numberOfCells ||
		board[line][column].isOpen || board[line][column].isFlag)
		return;

	else if (board[line][column].isBomb)
		return;
	
	else if (board[line][column].neighborBombCount > 0)
	{
		board[line][column].isOpen = 1;
		return;
	}

	board[line][column].isOpen = 1;

	revealCells(line - 1, column, board, numberOfCells); 
	revealCells(line + 1, column, board, numberOfCells); 
	revealCells(line, column - 1, board, numberOfCells); 
	revealCells(line, column + 1, board, numberOfCells); 
}

void mouseClick(int posX, int posY, int numberOfCells, Board** board, Uint8 button)
{
	int line, column;
	if (mouseCellIntersection)
	{
		getPos(posX, posY, numberOfCells, &line, &column, board);
		if (!board[line][column].isOpen)
		{
			if (button == SDL_BUTTON_LEFT)
			{
				if (!board[line][column].isBomb)
					revealCells(line, column, board, numberOfCells);
				else
					board[line][column].isOpen = 1;
			}
			else if (button == SDL_BUTTON_RIGHT)
			{
				board[line][column].isFlag = ~board[line][column].isFlag;
			}
		}
	}
}