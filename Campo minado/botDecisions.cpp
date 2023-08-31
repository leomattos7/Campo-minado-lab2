#include "botDecisions.h"


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

