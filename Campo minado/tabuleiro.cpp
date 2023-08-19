#include "tabuleiro.h"


Tabuleiro** alocaTabuleiro(int tamanho)
{
	Tabuleiro** tabuleiro = (Tabuleiro**)malloc(tamanho * sizeof(Tabuleiro*));
	for (int i = 0; i < tamanho; i++)
		tabuleiro[i] = (Tabuleiro*)malloc(tamanho * sizeof(Tabuleiro));

	return tabuleiro;
}

void inicializaTabuleiro(Tabuleiro** tabuleiro, int tamanho)
{
	int iniX = POS_INI_X - (tamanho * (TAM_CELULA / 2));
	int iniY = POS_INI_Y - (tamanho * (TAM_CELULA / 2));
	for (int i = 0; i < tamanho; i++)
		for (int j = 0; j < tamanho; j++)
		{
			tabuleiro[i][j].temBomba = 0;
			tabuleiro[i][j].temBandeira = 0;
			tabuleiro[i][j].qtdBombasVizinhas = 0;
			tabuleiro[i][j].revelado = 0;
			tabuleiro[i][j].posX = iniX + (i * TAM_CELULA);
			tabuleiro[i][j].posY = iniY + (j * TAM_CELULA);
		}
}

static void contarBombasVizinhas(int linha, int coluna, Tabuleiro** tabuleiro, int tamanho) 
{
	for (int i = -1; i <= 1; i++) 
		for (int j = -1; j <= 1; j++) 
		{
			int novaLinha = linha + i;
			int novaColuna = coluna + j;

			if (novaLinha >= 0 && novaLinha < tamanho && novaColuna >= 0 && novaColuna < tamanho) 
			{
				if (tabuleiro[novaLinha][novaColuna].temBomba) 
				{
					tabuleiro[linha][coluna].qtdBombasVizinhas++;
				}
			}
		}
}

static void contaBombasVizinhas(int qtdCelulas, Tabuleiro** tabuleiro)
{
	for (int i = 0; i < qtdCelulas; i++)
		for (int j = 0; j < qtdCelulas; j++)
		{
			if (tabuleiro[i][j].temBomba == 0)
				contarBombasVizinhas(i, j, tabuleiro, qtdCelulas);
		}
}

void sorteiaBombas(int qtdCelulas, Tabuleiro** tabuleiro)
{
	srand(time(NULL));
	int linha, coluna, i = 0;
	int qtdBombas = qtdCelulas * qtdCelulas * 0.15;
	while(i < qtdBombas)
	{
		linha = rand() % qtdCelulas;
		coluna = rand() % qtdCelulas;
		if (tabuleiro[linha][coluna].temBomba == 0)
		{
			tabuleiro[linha][coluna].temBomba = 1;
			i++;
		}
	}
	contaBombasVizinhas(qtdCelulas, tabuleiro);
}

void desenhaTabuleiro(int qtdCelulas, SDL_Renderer* renderer, const Textures& textures, Tabuleiro** tabuleiro)
{
	int posIniX = POS_INI_X - (qtdCelulas * (TAM_CELULA / 2));
	int posIniY = POS_INI_Y - (qtdCelulas * (TAM_CELULA / 2));

	for (int i = 0; i < qtdCelulas; i++)
	{
		for (int j = 0; j < qtdCelulas; j++)
		{
			int posX = posIniX + (i * TAM_CELULA);
			int posY = posIniY + (j * TAM_CELULA);

			SDL_Texture* textura = NULL;

			if (tabuleiro[i][j].revelado == 0)
			{
				textura = tabuleiro[i][j].temBandeira ? textures.bandeira : textures.celula;
			}
			else if (tabuleiro[i][j].revelado == 1)
			{
				textura = tabuleiro[i][j].temBomba ? textures.bomba : textures.celulaAberta;
			}

			setBack(posX, posY, renderer, textura);
		}
	}
}

void desenhaNumeros(int qtdCelulas, SDL_Renderer* renderer, const Textures& textures, Tabuleiro** tabuleiro)
{
	int posIniX = POS_INI_X - (qtdCelulas * (TAM_CELULA / 2));
	int posIniY = POS_INI_Y - (qtdCelulas * (TAM_CELULA / 2));

	for (int i = 0; i < qtdCelulas; i++)
	{
		for (int j = 0; j < qtdCelulas; j++)
		{
			if (tabuleiro[i][j].revelado == 1 && tabuleiro[i][j].qtdBombasVizinhas >= 1 && tabuleiro[i][j].qtdBombasVizinhas <= 4)
			{
				SDL_Texture* numeroTextura = textures.numeros[tabuleiro[i][j].qtdBombasVizinhas];
				setBack(posIniX + (i * TAM_CELULA), posIniY + (j * TAM_CELULA), renderer, numeroTextura);
			}
		}
	}
}