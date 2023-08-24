#include "botDecisions.h"


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
