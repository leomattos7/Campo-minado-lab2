#include "tabuleiro.h"


Board** memoryAlloc(int size)
{
	Board** board = new Board * [size];
	for (int i = 0; i < size; i++) {
		board[i] = new Board[size];
	}
	return board;
}

static void adjacentBombs(int line, int column, Board** board, int size) 
{
	for (int i = -1; i <= 1; i++) 
		for (int j = -1; j <= 1; j++) 
		{
			int newLine = line + i;
			int newColumn = column + j;

			if (newLine >= 0 && newLine < size && newColumn >= 0 && newColumn < size) 
			{
				if (board[newLine][newColumn].isBomb) 
				{
					board[line][column].nearbyBombs++;
				}
			}
		}
}

static void nearbyBombs(int numbOfCells, Board** board)
{
	for (int i = 0; i < numbOfCells; i++)
		for (int j = 0; j < numbOfCells; j++)
		{
			if (board[i][j].isBomb == 0)
				adjacentBombs(i, j, board, numbOfCells);
		}
}

void randomlyBombs(int numbOfCells, Board** board, int _linha, int _coluna)
{
	srand(time(NULL));
	int line, column, i = 0;
	int numbOfBombs = numbOfCells * numbOfCells * 0.15;
	while(i < numbOfBombs)
	{
		line = rand() % numbOfCells;
		column = rand() % numbOfCells;
		if (board[line][column].isBomb == 0
			&& line != _linha && column != _coluna)
		{
			board[line][column].isBomb = 1;
			i++;
		}
	}
	nearbyBombs(numbOfCells, board);
}


void setAditionalItems(SDL_Renderer* renderer, Textures texture, Items items)
{
	setBack(items.plusPositionX, items.plusPositionY, renderer, texture.plus);
}

void aditionalItemsPos(Items* items)
{
	items->plusPositionX = 50;
	items->plusPositionY = 30;
}

void setBoard(int numbOfCells, SDL_Renderer* renderer, const Textures* textures, Board** board)
{
	int posIniX = POS_INI_X - (numbOfCells * (CELL_SIZE / 2));
	int posIniY = POS_INI_Y - (numbOfCells * (CELL_SIZE / 2));

	for (int i = 0; i < numbOfCells; i++)
	{
		for (int j = 0; j < numbOfCells; j++)
		{
			int posX = posIniX + (i * CELL_SIZE);
			int posY = posIniY + (j * CELL_SIZE);

			SDL_Texture* texture = NULL;

			if (!board[i][j].isOpen)
			{
				if(board[i][j].isFlag)
					texture = textures->flag;
				else
					texture = board[i][j].color ? textures->cell[0] : textures->cell[1];
			}
			else if (board[i][j].isOpen == 1)
			{
				if(board[i][j].isBomb)
					texture = board[i][j].selected ? textures->redBomb : textures->bomb;
				else
					texture = textures->openCell;
			}
			setBack(posX, posY, renderer, texture);
		}
	}
}

void setNumbers(int numbOfCells, SDL_Renderer* renderer, const Textures* textures, Board** board)
{
	int posIniX = POS_INI_X - (numbOfCells * (CELL_SIZE / 2));
	int posIniY = POS_INI_Y - (numbOfCells * (CELL_SIZE / 2));

	for (int i = 0; i < numbOfCells; i++)
	{
		for (int j = 0; j < numbOfCells; j++)
		{
			if (board[i][j].isOpen == 1 && board[i][j].nearbyBombs >= 1 && board[i][j].nearbyBombs <= 4)
			{
				SDL_Texture* numTexture = textures->numbers[board[i][j].nearbyBombs];
				setBack(posIniX + (i * CELL_SIZE), posIniY + (j * CELL_SIZE), renderer, numTexture);
			}
		}
	}
}