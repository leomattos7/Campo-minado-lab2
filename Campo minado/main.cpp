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

    Game game;
    game.size = 12;
    game.reallocUp = 0;

    Items items;
    aditionalItemsPos(&items);

    Board** board = memoryAlloc(game.size);
    initBoard(board, game.size, &game.gameStart);

    SDL_RenderClear(renderer);
    setBack(0, 0, renderer, textures.board);
    setAditionalItems(renderer, textures, items);

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
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                mousex = event.button.x;
                mousey = event.button.y;
                if (event.button.button == SDL_BUTTON_LEFT)
                    mouseClick(mousex, mousey, &game, board, items, SDL_BUTTON_LEFT);
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseClick(mousex, mousey, &game, board, items, SDL_BUTTON_RIGHT);
            }
        }
        if (game.gameStart == 1)
        {
            randomlyBombs(game.size, board);
            game.gameStart = -1;
        }
        setBoard(game.size, renderer, &textures, board);
        setNumbers(game.size, renderer, &textures, board);
        SDL_RenderPresent(renderer);
        if (game.reallocUp == 1)
        {
			game.reallocUp = 0;
            game.size++;
            Board** newBoard = memoryAlloc(game.size);
            initBoard(newBoard, game.size, &game.gameStart);
            board = newBoard;
		}
    }

    SDL_DestroyTexture(textures.board);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}