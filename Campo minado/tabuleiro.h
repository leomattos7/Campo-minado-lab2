#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <SDL.h>
#include <stdio.h>
#include "imagens.h"

typedef struct
{
    int temBomba;
    int temBandeira;
    int qtdBombasVizinhas;
    int revelado;
}Tabuleiro;

void* alocaTabuleiro(Tabuleiro** tabuleiro, int tamanho);

void* inicializaTabuleiro(Tabuleiro** tabuleiro, int tamanho);

void desenhaTabuleiro(int qtdCelulas, SDL_Renderer* renderer, SDL_Texture* celula, SDL_Texture* bomba,
    SDL_Texture* celulaAberta, SDL_Texture* bandeira, Tabuleiro** tabuleiro);

#endif 
