#include <SDL.h>
#include "imagens.h"
#include "tabuleiro.h"

/*Adicionar tabuleiro.cpp, nesse arquivo: criar struct do tipo tabuleiro que recebe as informações da struct Tabuleiro e desenha ela na tela*/

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("Posicionando Imagem", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* tabuleiro = loadTexture(renderer, "tabuleiro.bmp");
    SDL_Texture* celula = loadTexture(renderer, "cell.bmp");
    SDL_Texture* bomba = loadTexture(renderer, "cell_bomba.bmp");
    SDL_Texture* bandeira = loadTexture(renderer, "cell_flag.bmp");
    SDL_Texture* celulaAberta = loadTexture(renderer, "cell_open.bmp");
    SDL_Texture** score = (SDL_Texture**)malloc(2 * sizeof(SDL_Texture*));
    for (int i = 0; i < 2; i++) 
        score[i] = loadTexture(renderer, "score.bmp");
    
    int running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        setBack(0, 0, renderer, tabuleiro);
        setBack(30, 30, renderer, score[0]);
        setBack(350, 300, renderer, celula);
        setBack(410, 300, renderer, bomba);
        setBack(380, 300, renderer, bandeira);
        setBack(350, 330, renderer, celulaAberta);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(tabuleiro);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}