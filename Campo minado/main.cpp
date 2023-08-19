#include <SDL.h>
#include "imagens.h"
#include "tabuleiro.h"
#include "game.h"

/*Adicionar tabuleiro.cpp, nesse arquivo: criar struct do tipo tabuleiro que recebe as informações da struct Tabuleiro e desenha ela na tela*/

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Campo Minado by: Leonardo de Mattos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    Textures textures;
    loadTextures(renderer, textures);

    int qtdCelulas = 12;

    Tabuleiro** campo = alocaTabuleiro(qtdCelulas);
    inicializaTabuleiro(campo, qtdCelulas);
    sorteiaBombas(qtdCelulas, campo);

    SDL_RenderClear(renderer);
    setBack(0, 0, renderer, textures.tabuleiro);

    int running = 1;
    int mousex = 0, mousey = 0;
    SDL_Event event;
    
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mousex = event.button.x;
                mousey = event.button.y;
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouseClick(mousex, mousey, qtdCelulas, campo, SDL_BUTTON_LEFT);
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseClick(mousex, mousey, qtdCelulas, campo, SDL_BUTTON_RIGHT);
            }
        }
        desenhaTabuleiro(qtdCelulas, renderer, &textures, campo);
        desenhaNumeros(qtdCelulas, renderer, &textures, campo);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textures.tabuleiro);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}