#include "botDecisions.h"

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
	return qtdFlags;
}

static int searchFreeCell(Game* game, Board** board, int i, int j)
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
				{
					playCell(board, game, newRow, newCol, 1);
					board[newRow][newCol].selected = 1;
					return 1;
				}
			}
		}
	}
	return 0;
}


static int playBot(Game* game, Board** board)
{
	int play = 0;
	for (int i = 0; i < game->size; i++)
	{
		for (int j = 0; j < game->size; j++)
		{
			if (board[i][j].isOpen == 1)
			{
				int flagsAround = searchFlag(game, board, i, j);
				if (flagsAround == board[i][j].nearbyBombs)
				{
					play = searchFreeCell(game, board, i, j);
				}
			}
			if (play == 1)
				return 1;
		}
	}
	return 0;
}

static void randomCell(list<CellBot>& cells, Board** board, Game* game)
{
	if (cells.empty())
	{
		return;
	}
	srand(static_cast<unsigned>(time(nullptr)));
	int randomIndex = rand() % cells.size();
	auto it = cells.begin();
	advance(it, randomIndex);
	board[it->row][it->col].selected = 1;
	playCell(board, game, it->row, it->col, 1);
}

static void randomPlay(Board** board, Game* game)
{
	int newRow, newCol;
	list<CellBot> cells;
	for (int i = 0; i < game->size; i++)
	{
		for (int j = 0; j < game->size; j++)
		{
			if (board[i][j].isOpen == 0 && board[i][j].isFlag == 0)
			{
				cells.push_front({ i, j });
			}
		}
	}
	randomCell(cells, board, game);
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
				if (board[newRow][newCol].isFlag == 0)
					closedCount++;
			}
		}
	}
	return closedCount;
}

static void setFlag(Board** board, Game* game, int i, int j)
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
				{
					playCell(board, game, newRow, newCol, 3);
					return;
				}
			}
		}
	}
}

static int searchPossibleBombs(Board** board, Game* game)
{
	for (int i = 0; i < game->size; i++)
	{
		for (int j = 0; j < game->size; j++)
		{
			if (board[i][j].isOpen == 1 && board[i][j].nearbyBombs > 0)
			{
				if (board[i][j].nearbyBombs == countClosedCells(board, game->size, i, j))
				{
					setFlag(board, game, i, j);
					return 1;
				}
			}
		}
	}
	return 0;
}

void playing(Board** board, Game* game)
{
	if (playBot(game, board))
	{
		return;
	}
	else if (searchPossibleBombs(board, game))
	{
		return;
	}
	else
	{
		randomPlay(board, game);
		return;
	}
}

