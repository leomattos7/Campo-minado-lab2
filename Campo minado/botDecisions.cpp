#include "botDecisions.h"

// ainda falta fazer o jogo funcionar, mas isso está pronto, basta utilizar as funções de game.cpp
static int calcProbability(Game* game, Bot bot)
{
	// decidir jogada inicial
	// decidir entre celulas perto de celulas com bombas vizinhas e celulas sem bombas vizinhas
	// decidir entre celulas centrais e das bordas
}
void readMatrix(Board** board, Game* game, Bot bot)
{
	int aux = 0;
	bot.probability = 0;
	for (int i = 0; i < game->size; i++)
	{
		for (int j = 0; j < game->size; j++)
		{
			if (bot.probability > aux)
			{
				aux = bot.probability;
				bot.iPos = i;
				bot.jPos = j;
			}
		}
	}
}
