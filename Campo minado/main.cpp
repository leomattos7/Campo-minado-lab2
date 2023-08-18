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
    SDL_Texture* tabuleiro = loadTexture(renderer, "tabuleiro.bmp");
    SDL_Texture* celula = loadTexture(renderer, "cell.bmp");
    SDL_Texture* bomba = loadTexture(renderer, "cell_bomba.bmp");
    SDL_Texture* bandeira = loadTexture(renderer, "cell_flag.bmp");
    SDL_Texture* celulaAberta = loadTexture(renderer, "cell_open.bmp");
    SDL_Texture* score = loadTexture(renderer, "score.bmp");
    SDL_Texture* num1 = loadTexture(renderer, "one.bmp");
    SDL_Texture* num2 = loadTexture(renderer, "two.bmp");
    SDL_Texture* num3 = loadTexture(renderer, "three.bmp");
    SDL_Texture* num4 = loadTexture(renderer, "four.bmp");

    int qtdCelulas = 12;

    Tabuleiro** campo = alocaTabuleiro(qtdCelulas);
    inicializaTabuleiro(campo, qtdCelulas);
    sorteiaBombas(qtdCelulas, campo);

    SDL_RenderClear(renderer);
    setBack(0, 0, renderer, tabuleiro);

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
                if(event.button.button == SDL_BUTTON_LEFT)
					mouseClickLeft(mousex, mousey, qtdCelulas, campo);
                if(event.button.button == SDL_BUTTON_RIGHT)
                    mouseClickRight(mousex, mousey, qtdCelulas, campo);
            }
        }
        desenhaTabuleiro(qtdCelulas, renderer, celula, bomba, celulaAberta, bandeira, campo);
        desenhaNumeros(qtdCelulas, renderer, num1, num2, num3, num4, campo);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(tabuleiro);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}