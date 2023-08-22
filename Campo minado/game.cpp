#include "game.h"

static int pertence(int posX, int posY, int qtdCelulas)
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
				campo[i][j].selected = 1;
				return;
			}
}

static void revelaCelulas(int linha, int coluna, Board** tabuleiro, int qtdCelulas)
{
	if (linha < 0 || linha >= qtdCelulas || coluna < 0 || coluna >= qtdCelulas ||
		tabuleiro[linha][coluna].isOpen || tabuleiro[linha][coluna].isFlag)
		return;

	else if (tabuleiro[linha][coluna].isBomb)
		return;
	
	else if (tabuleiro[linha][coluna].nearbyBombs > 0)
	{
		tabuleiro[linha][coluna].isOpen = 1;
		return;
	}

	tabuleiro[linha][coluna].isOpen = 1;

	revelaCelulas(linha - 1, coluna, tabuleiro, qtdCelulas); 
	revelaCelulas(linha + 1, coluna, tabuleiro, qtdCelulas); 
	revelaCelulas(linha, coluna - 1, tabuleiro, qtdCelulas); 
	revelaCelulas(linha, coluna + 1, tabuleiro, qtdCelulas); 
}

static void revealBombs(int numOfCells, Board** board)
{
	for (int i = 0; i < numOfCells; i++)
		for (int j = 0; j < numOfCells; j++)
			if (board[i][j].isBomb)
				board[i][j].isOpen = 1;
}

static int clickItem(int posX, int posY, int itemPosX, int itemPosY)
{
	if (posX >= itemPosX && posX <= itemPosX + 40 &&
		posY >= itemPosY && posY <= itemPosY + 40)
	{
		return 1;
	}
	return 0;
}

void mouseClick(int posX, int posY, Game* game, Board** board, Items item, Uint8 button)
{
	int linha, coluna;
	if (pertence(posX, posY, game->size))
	{
		getPos(posX, posY, game->size, &linha, &coluna, board);
		if (!board[linha][coluna].isOpen)
		{
			if (button == SDL_BUTTON_LEFT)
			{
				if (!board[linha][coluna].isBomb)
				{
					revelaCelulas(linha, coluna, board, game->size);
					board[linha][coluna].selected = 0;
				}
				else
				{
					revealBombs(game->size, board);
				}
			}
			else if (button == SDL_BUTTON_RIGHT)
			{
				board[linha][coluna].isFlag = ~board[linha][coluna].isFlag;
				board[linha][coluna].selected = 0;
			}
		}
	}
	else if (clickItem(posX, posY, item.plusPositionX, item.plusPositionY))
	{
		board = (Board**)realloc(board, sizeof(Board*) * (game->size + 1));
		for (int i = 0; i < game->size; i++)
			board[i] = (Board*)realloc(board[i], sizeof(Board) * (game->size + 1));
		initBoard(board, game->size++);
	}
}