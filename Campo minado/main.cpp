#include <SDL.h>
#include "imagens.h"
#include "tabuleiro.h"
#include "game.h"
#include "botDecisions.h"

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Campo Minado by: Leonardo de Mattos", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Textures textures;
    loadTextures(renderer, textures);
    Game game;
    initGame(&game);
    Items items;
    aditionalItemsPos(&items);
    Board** board = memoryAlloc(game.size);
    initBoard(board, game.size);
    setInitialTextures(renderer, &textures, items);
    SDL_Event event;    
    while (game.running)
    {
        if (game.gameMode == 0)
        {
            while (SDL_PollEvent(&event))
            {
                events(event, &game, board, items);
            }
        }
        else if (game.gameOver == 0)
        {
            playing(board, &game);
            updateBot(&game, renderer, &textures, board);
        }
        if (game.reallocUp)
        {
            deleteBoard(board, game.size);
            reallocBoard(&game, &board);
            setInitialTextures(renderer, &textures, items);
		}
        update(&game, renderer, &textures, board);
    }
    dispose(&renderer, &window);
    return 0;
}