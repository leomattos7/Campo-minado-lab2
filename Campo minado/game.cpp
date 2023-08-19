#include "game.h"

static int pertence(int posX, int posY, int qtdCelulas)
{
	int xIni = POS_INI_X - (qtdCelulas * (TAM_CELULA / 2));
	int xFim = POS_INI_X + (qtdCelulas * (TAM_CELULA / 2));
	int yIni = POS_INI_Y - (qtdCelulas * (TAM_CELULA / 2));
	int yFim = POS_INI_Y + (qtdCelulas * (TAM_CELULA / 2));
	if(posX >= xIni && posX <= xFim && posY >= yIni && posY <= yFim)
		return 1;
	return 0;
}

static void getPos(int posX, int posY, int qtdCelulas, int* linha, int* coluna, Tabuleiro** campo)
{
	for(int i = 0; i < qtdCelulas; i++)
		for(int j = 0; j < qtdCelulas; j++)
			if (posX >= campo[i][j].posX && posX <= campo[i][j].posX + TAM_CELULA &&
				posY >= campo[i][j].posY && posY <= campo[i][j].posY + TAM_CELULA)
			{
				*linha = i;
				*coluna = j;
				return;
			}
}

static void revelaCelulas(int linha, int coluna, Tabuleiro** tabuleiro, int qtdCelulas)
{
	if (linha < 0 || linha >= qtdCelulas || coluna < 0 || coluna >= qtdCelulas ||
		tabuleiro[linha][coluna].revelado || tabuleiro[linha][coluna].temBandeira)
		return;

	else if (tabuleiro[linha][coluna].temBomba)
		return;
	
	else if (tabuleiro[linha][coluna].qtdBombasVizinhas > 0)
	{
		tabuleiro[linha][coluna].revelado = 1;
		return;
	}

	tabuleiro[linha][coluna].revelado = 1;

	revelaCelulas(linha - 1, coluna, tabuleiro, qtdCelulas); 
	revelaCelulas(linha + 1, coluna, tabuleiro, qtdCelulas); 
	revelaCelulas(linha, coluna - 1, tabuleiro, qtdCelulas); 
	revelaCelulas(linha, coluna + 1, tabuleiro, qtdCelulas); 
}

void mouseClick(int posX, int posY, int qtdCelulas, Tabuleiro** campo, Uint8 button)
{
	int linha, coluna;
	if (pertence)
	{
		getPos(posX, posY, qtdCelulas, &linha, &coluna, campo);
		if (!campo[linha][coluna].revelado)
		{
			if (button == SDL_BUTTON_LEFT)
			{
				if (!campo[linha][coluna].temBomba)
					revelaCelulas(linha, coluna, campo, qtdCelulas);
				else
					campo[linha][coluna].revelado = 1;
			}
			else if (button == SDL_BUTTON_RIGHT)
			{
				campo[linha][coluna].temBandeira = ~campo[linha][coluna].temBandeira;
			}
		}
	}
}