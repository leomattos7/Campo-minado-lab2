#include "botDecisions.h"
/*
static int countClosedCells(Board** board, int size, int i, int j)
{
	int closedCount = 0, newRow, newCol;
	for (int linha = -1; linha < 2; linha++)
	{
		for (int coluna = -1; coluna < 2; coluna++)
		{
			newRow = i + linha;
			newCol = j + coluna;
			if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size && board[newRow][newCol].isOpen == 0)
			{
				if (board[newRow][newCol].isFlag == 0)
					closedCount++;
			}
		}
	}

	return closedCount;
}

static int searchFlag(Game* game, Board** board, int i, int j)
{
	int newRow, newCol;
	int qtdFlags = 0;
	for (int linha = -1; linha < 2; linha++)
	{
		for (int coluna = -1; coluna < 2; coluna++)
		{
			newRow = i + linha;
			newCol = j + coluna;
			if (newRow >= 0 && newRow < game->size && newCol >= 0 && newCol < game->size && board[newRow][newCol].isFlag != 0)
			{
				qtdFlags++;
			}
		}
	}
	std::cout << i << " " << j << " " << qtdFlags << std::endl;
	return qtdFlags;
}

static void searchFreeCell(Game* game, Board** board, int i, int j)
{
	int newRow, newCol;
	for (int linha = -1; linha < 2; linha++)
	{
		for (int coluna = -1; coluna < 2; coluna++)
		{
			newRow = i + linha;
			newCol = j + coluna;

			if (newRow >= 0 && newRow < game->size && newCol >= 0 && newCol < game->size && board[newRow][newCol].isOpen == 0)
			{
				if (board[newRow][newCol].isFlag == 0)
					board[newRow][newCol].isOpen = 1;
			}
		}
	}
}


static void playBot(Game* game, Board** board)
{
	for (int i = 0; i < game->size; i++)
	{
		for (int j = 0; j < game->size; j++)
		{
			if (board[i][j].isOpen == 1)
			{
				int flagsAround = searchFlag(game, board, i, j);
				if (flagsAround == board[i][j].nearbyBombs)
					searchFreeCell(game, board, i, j);
			}
		}
	}
}

static int countClosedCells(Board** board, int size, int i, int j)
{
	int closedCount = 0, newRow, newCol;
	for (int linha = -1; linha < 2; linha++)
	{
		for (int coluna = -1; coluna < 2; coluna++)
		{
			newRow = i + linha;
			newCol = j + coluna;
			if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size && board[newRow][newCol].isOpen == 0)
			{
				closedCount++;
			}
		}
	}
	return closedCount;
}

static void setFlag(Board** board, int size, int i, int j)
{
	int newRow, newCol;
	for (int linha = -1; linha < 2; linha++)
	{
		for (int coluna = -1; coluna < 2; coluna++)
		{
			newRow = i + linha;
			newCol = j + coluna;
			if (newRow >= 0 && newRow < size && newCol >= 0 && newCol < size && board[newRow][newCol].isOpen == 0)
			{
				board[newRow][newCol].isFlag = 1;
			}
		}
	}
}

static void searchPossibleBombs(Board** board, Game* game)
{
	for (int i = 0; i < game->size; i++)
	{
		for (int j = 0; j < game->size; j++)
		{
			if (board[i][j].isOpen == 1 && board[i][j].nearbyBombs > 0)
			{
				if (board[i][j].nearbyBombs == countClosedCells(board, game->size, i, j))
				{
					setFlag(board, game->size, i, j);
				}
			}
		}
	}
}
*/
