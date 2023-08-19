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

    int numberOfCells = 12;

    Board** board = memoryAlloc(numberOfCells);
    initBoard(board, numberOfCells);
    randomlyGenerateBombs(numberOfCells, board);

    SDL_RenderClear(renderer);
    setBack(0, 0, renderer, textures.board);

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
                    mouseClick(mousex, mousey, numberOfCells, board, SDL_BUTTON_LEFT);
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseClick(mousex, mousey, numberOfCells, board, SDL_BUTTON_RIGHT);
            }
        }
        setBoard(numberOfCells, renderer, &textures, board);
        setNumbers(numberOfCells, renderer, &textures, board);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(textures.board);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}