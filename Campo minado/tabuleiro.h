#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <SDL.h>
#include <stdio.h>
#include "imagens.h"
#include <time.h>
#include <stdlib.h>

#define POS_INI_X 400
#define POS_INI_Y 330
#define TAM_CELULA 30

typedef struct
{
    int temBomba;
    int temBandeira;
    int qtdBombasVizinhas;
    int revelado;

    int posX;
    int posY;
}Tabuleiro;

Tabuleiro** alocaTabuleiro(int tamanho);

void inicializaTabuleiro(Tabuleiro** tabuleiro, int tamanho);

void desenhaTabuleiro(int qtdCelulas, SDL_Renderer* renderer, SDL_Texture* celula, SDL_Texture* bomba,
    SDL_Texture* celulaAberta, SDL_Texture* bandeira, Tabuleiro** tabuleiro);

void sorteiaBombas(int qtdCelulas, Tabuleiro** tabuleiro);

void desenhaNumeros(int qtdCelulas, SDL_Renderer* renderer, SDL_Texture* um,
    SDL_Texture* dois, SDL_Texture* three, SDL_Texture* four, Tabuleiro** tabuleiro);

#endif 
