#include "game.h"

void initBoard(Board** board, int size)
{
	int iniX = POS_INI_X - (size * (CELL_SIZE / 2));
	int iniY = POS_INI_Y - (size * (CELL_SIZE / 2));
	int color = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j].isBomb = 0;
			board[i][j].isOpen = 0;
			board[i][j].isFlag = 0;
			board[i][j].nearbyBombs = 0;
			board[i][j].selected = 0;
			if (color)
				board[i][j].color = 1;
			else
				board[i][j].color = 0;
			board[i][j].posX = iniX + (i * CELL_SIZE);
			board[i][j].posY = iniY + (j * CELL_SIZE);
			color = ~color;
		}
		if (size % 2 == 0)
			color = ~color;
	}
}

void initGame(Game* game)
{
	if(game->restartGame != 1)
		game->size = 12;
	game->reallocUp = 0;
	game->menu = 1;
	game->running = 1;
	game->gameMode = 0;
	game->restartGame = 0;
	game->gameOver = 0;
	game->gameStart = 0;
	game->nOfBombs = 0;
	game->openCells = 0;
}

void events(SDL_Event event, Game* game, Board** board, Items item)
{
	if (event.type == SDL_QUIT)
	{
		game->running = 0;
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		int mousex = event.button.x;
		int mousey = event.button.y;
		if (event.button.button == SDL_BUTTON_LEFT)
			mouseClick(mousex, mousey, game, board, item, SDL_BUTTON_LEFT);
		else if (event.button.button == SDL_BUTTON_RIGHT)
			mouseClick(mousex, mousey, game, board, item, SDL_BUTTON_RIGHT);
	}
}

void dispose(SDL_Renderer** renderer, SDL_Window** window)
{
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);
	*renderer = NULL;
	*window = NULL;
	SDL_Quit();
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
				if(board[newRow][newCol].isFlag == 0)
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
				if(flagsAround == board[i][j].nearbyBombs)
					searchFreeCell(game, board, i, j);
			}
		}
	}
}

void update(Game* game, SDL_Renderer* renderer, Textures* textures, Board** board)
{
	if (game->restartGame)
	{
		initGame(game);
		initBoard(board, game->size);
		game->restartGame = 0;
	}
	setBoard(game->size, renderer, textures, board);
	setNumbers(game->size, renderer, textures, board);
	SDL_RenderPresent(renderer);
}

void setInitialTextures(SDL_Renderer* renderer, Textures* textures, Items items)
{
	SDL_RenderClear(renderer);
	setBack(0, 0, renderer, textures->board);
	setAditionalItems(renderer, textures, items);
}

void deleteBoard(Board** board, int size)
{
	for (int i = 0; i < size; i++)
		delete[] board[i];
	delete[] board;
}

void reallocBoard(Game* game, Board*** board)
{
	game->reallocUp = 0;
	if (game->size == 16)
		game->size = 8;
	else
		game->size++;
	Board** newBoard = memoryAlloc(game->size);
	initBoard(newBoard, game->size);
	game->gameStart = 0;
	*board = (Board**)newBoard;
}

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


static void randomlyBombs(int numbOfCells, Board** board, int _linha, int _coluna)
{
	srand(time(NULL));
	int line, column, i = 0;
	int numbOfBombs = numbOfCells * numbOfCells * 0.15;
	while (i < numbOfBombs)
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
	if (pertence(posX, posY, game->size) && game->gameOver == 0)
	{
		getPos(posX, posY, game->size, &linha, &coluna, board);
		if (!board[linha][coluna].isOpen)
		{
			if (button == SDL_BUTTON_LEFT)
			{
				if (!board[linha][coluna].isBomb)
				{
					if (game->gameStart == 0)
					{
						game->gameStart = 1;
						randomlyBombs(game->size, board, linha, coluna);
					}
					revelaCelulas(linha, coluna, board, game->size);
					board[linha][coluna].selected = 0;
				}
				else
				{
					game->gameOver = 1;
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
	else if (clickItem(posX, posY, item.plusPositionX, item.plusPositionY) && game->gameOver == 0)
	{
		game->reallocUp = 1;
	}
	else if (clickItem(posX, posY, item.restartPositionX, item.restartPositionY))
	{
		game->restartGame = 1;
	}
	else
		playBot(game, board);
}