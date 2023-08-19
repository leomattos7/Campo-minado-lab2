#include "tabuleiro.h"


Board** memoryAlloc(int size)
{
	Board** tabuleiro = (Board**)calloc(size, sizeof(Board*));
	for (int i = 0; i < size; i++)
		tabuleiro[i] = (Board*)calloc(size, sizeof(Board));

	return tabuleiro;
}

void initBoard(Board** board, int tamanho)
{
	int iniX = POS_INI_X - (tamanho * (CELL_SIZE / 2));
	int iniY = POS_INI_Y - (tamanho * (CELL_SIZE / 2));
	for (int i = 0; i < tamanho; i++)
		for (int j = 0; j < tamanho; j++)
		{
			board[i][j].posX = iniX + (i * CELL_SIZE);
			board[i][j].posY = iniY + (j * CELL_SIZE);
		}
}

static void countNearbyBombs(int line, int column, Board** board, int size) 
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
					board[line][column].neighborBombCount++;
				}
			}
		}
}

static void countAdjacentBombs(int qtdCells, Board** board)
{
	for (int i = 0; i < qtdCells; i++)
		for (int j = 0; j < qtdCells; j++)
		{
			if (board[i][j].isBomb == 0)
				countNearbyBombs(i, j, board, qtdCells);
		}
}

void randomlyGenerateBombs(int numberOfCells, Board** board)
{
	srand(time(NULL));
	int line, column, i = 0;
	int numberOfBombs = numberOfCells * numberOfCells * 0.15;
	while(i < numberOfBombs)
	{
		line = rand() % numberOfCells;
		column = rand() % numberOfCells;
		if (board[line][column].isBomb == 0)
		{
			board[line][column].isBomb = 1;
			i++;
		}
	}
	countAdjacentBombs(numberOfCells, board);
}

void setBoard(int numberOfCells, SDL_Renderer* renderer, const Textures* textures, Board** board)
{
	int posIniX = POS_INI_X - (numberOfCells * (CELL_SIZE / 2));
	int posIniY = POS_INI_Y - (numberOfCells * (CELL_SIZE / 2));

	for (int i = 0; i < numberOfCells; i++)
	{
		for (int j = 0; j < numberOfCells; j++)
		{
			int posX = posIniX + (i * CELL_SIZE);
			int posY = posIniY + (j * CELL_SIZE);

			SDL_Texture* textura = NULL;

			if (board[i][j].isOpen == 0)
			{
				textura = board[i][j].isFlag ? textures->flag : textures->cell;
			}
			else if (board[i][j].isOpen == 1)
			{
				textura = board[i][j].isBomb ? textures->cell : textures->openCell;
			}

			setBack(posX, posY, renderer, textura);
		}
	}
}

void setNumbers(int numberOfCells, SDL_Renderer* renderer, const Textures* textures, Board** board)
{
	int posIniX = POS_INI_X - (numberOfCells * (CELL_SIZE / 2));
	int posIniY = POS_INI_Y - (numberOfCells * (CELL_SIZE / 2));

	for (int i = 0; i < numberOfCells; i++)
	{
		for (int j = 0; j < numberOfCells; j++)
		{
			if (board[i][j].isOpen == 1 && board[i][j].neighborBombCount >= 1 && board[i][j].neighborBombCount <= 4)
			{
				SDL_Texture* numeroTextura = textures->numbers[board[i][j].neighborBombCount];
				setBack(posIniX + (i * CELL_SIZE), posIniY + (j * CELL_SIZE), renderer, numeroTextura);
			}
		}
	}
}