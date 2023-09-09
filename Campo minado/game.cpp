#include "game.h"

void initBoard(Board** board, int size)
{
	int iniX = POS_INI_X - (size * (CELL_SIZE / 2));
	int iniY = POS_INI_Y - (size * (CELL_SIZE / 2));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			board[i][j].isBomb = 0;
			board[i][j].isOpen = 0;
			board[i][j].isFlag = 0;
			board[i][j].nearbyBombs = 0;
			board[i][j].selected = 0;
			board[i][j].posX = iniX + (i * CELL_SIZE);
			board[i][j].posY = iniY + (j * CELL_SIZE);
		}
	}
}

void initGame(Game* game)
{
	if (game->restartGame != 1)
	{
		game->size = 12;
	}
	game->reallocUp = 0;
	game->running = 1;
	game->restartGame = 0;
	game->gameMode = 0;
	game->gameOver = 0;
	game->gameStart = 0;
	game->nOfBombs = 0;
	game->openCells = 0;
}

void updateBot(Game* game, SDL_Renderer* renderer, const Textures* textures, Board** board)
{
	int posIniX = POS_INI_X - (game->size * (CELL_SIZE / 2));
	int posIniY = POS_INI_Y - (game->size * (CELL_SIZE / 2));
	
	for (int i = 0; i < game->size; i++)
	{
		for (int j = 0; j < game->size; j++)
		{
			int posX = posIniX + (i * CELL_SIZE);
			int posY = posIniY + (j * CELL_SIZE);
			if (board[i][j].selected == 1)
			{
				setBack(posX, posY, renderer, textures->cellSelect);
				if(board[i][j].isFlag != 0 || board[i][j].isBomb == 0)
					board[i][j].selected = 0;
				SDL_RenderPresent(renderer);
				SDL_Delay(800);
			}
		}
	}
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
	if (game->gameOver == 1 && game->gameMode == 1)
	{
		initGame(game);
	}
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

static void revealCells(int row, int col, Board** tabuleiro, int qtdCelulas)
{
	if (row < 0 || row >= qtdCelulas || col < 0 || col >= qtdCelulas)
	{
		return;
	} 
	else if (tabuleiro[row][col].isOpen || tabuleiro[row][col].isFlag)
	{
		return;
	}
	else if (tabuleiro[row][col].isBomb)
	{
		return;
	}
	else if (tabuleiro[row][col].nearbyBombs > 0)
	{
		tabuleiro[row][col].isOpen = 1;
		return;
	}
	tabuleiro[row][col].isOpen = 1;
	revealCells(row - 1, col, tabuleiro, qtdCelulas); 
	revealCells(row + 1, col, tabuleiro, qtdCelulas); 
	revealCells(row, col - 1, tabuleiro, qtdCelulas); 
	revealCells(row, col + 1, tabuleiro, qtdCelulas); 
}


static void randomlyBombs(int numbOfCells, Board** board, int _linha, int _coluna)
{
	srand(static_cast<unsigned>(time(nullptr)));
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

void playCell(Board** board, Game* game, int row, int col, int button)
{
	board[row][col].selected = 1;
	if (button == 1)
	{
		if (!board[row][col].isBomb)
		{
			if (game->gameStart == 0)
			{
				game->gameStart = 1;
				randomlyBombs(game->size, board, row, col);
			}
			revealCells(row, col, board, game->size);
		}
		else
		{
			game->gameOver = 1;
			revealBombs(game->size, board);
		}
	}
	else if (button == 3)
	{
		board[row][col].isFlag = ~board[row][col].isFlag;
	}
	if (game->gameMode == 0 && game->gameOver == 0)
		board[row][col].selected = 0;
}

void mouseClick(int posX, int posY, Game* game, Board** board, Items item, Uint8 button)
{
	int row, col;
	if (pertence(posX, posY, game->size) && game->gameOver == 0 && game->gameMode == 0)
	{
		getPos(posX, posY, game->size, &row, &col, board);
		if (!board[row][col].isOpen)
		{
			playCell(board, game, row, col, button);
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
	else if(clickItem(posX, posY, item.roboPositionX, item.roboPositionY))
	{
		if (game->gameMode == 0)
			game->gameMode = 1;
		else
			initGame(game);
	}	
}