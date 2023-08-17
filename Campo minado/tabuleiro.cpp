#include "tabuleiro.h"

/*void* alocaTabuleiro(Tabuleiro** tabuleiro, int tamanho)
{
	tabuleiro = (Tabuleiro**)malloc(tamanho * sizeof(Tabuleiro*));
	for (int i = 0; i < tamanho; i++)
		tabuleiro[i] = (Tabuleiro*)malloc(tamanho * sizeof(Tabuleiro));
}

void* inicializaTabuleiro(Tabuleiro** tabuleiro, int tamanho)
{
	for (int i = 0; i < tamanho; i++)
		for (int j = 0; j < tamanho; j++)
		{
			tabuleiro[i][j].temBomba = 0;
			tabuleiro[i][j].temBandeira = 0;
			tabuleiro[i][j].qtdBombasVizinhas = 0;
			tabuleiro[i][j].revelado = 0;
		}
}

void desenhaTabuleiro(int qtdCelulas, SDL_Renderer* renderer, SDL_Texture* celula, SDL_Texture* bomba,
					SDL_Texture* celulaAberta, SDL_Texture* bandeira, Tabuleiro** tabuleiro)
{
	int posIniX = 400 - (qtdCelulas * 15);
	int posIniY = 300 - (qtdCelulas * 15);
	for (int i = 0; i < qtdCelulas; i++)
		for (int j = 0; j < qtdCelulas; j++)
		{
			if(tabuleiro[i][j].revelado == 0)
			{
				if (tabuleiro[i][j].temBandeira == 1)
					setBack(posIniX + (i * 30), posIniY + (j * 30), renderer, bandeira);
				else setBack(posIniX + (i * 30), posIniY + (j * 30), renderer, celula);
			}
			else if (tabuleiro[i][j].revelado == 1)
				if (tabuleiro[i][j].temBomba == 1)
					setBack(posIniX + (i * 30), posIniY + (j * 30), renderer, bomba);
				else setBack(posIniX + (i * 30), posIniY + (j * 30), renderer, celulaAberta);
}	*/