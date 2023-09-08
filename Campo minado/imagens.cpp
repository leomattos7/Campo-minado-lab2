#include "imagens.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file)
{
    SDL_Surface* bitmap = SDL_LoadBMP(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
    return texture;
}

void loadTextures(SDL_Renderer* renderer, Textures& textures) 
{
    textures.board = loadTexture(renderer, "./resources/tabuleiro.bmp");
    textures.cell = loadTexture(renderer, "./resources/cell.bmp");
    textures.cellSelect = loadTexture(renderer, "./resources/cell_select.bmp");
    textures.bomb = loadTexture(renderer, "./resources/cell_bomba.bmp");
    textures.flag = loadTexture(renderer, "./resources/cell_flag.bmp");
    textures.openCell = loadTexture(renderer, "./resources/cell_open.bmp");
    textures.score = loadTexture(renderer, "./resources/score.bmp");
    textures.redBomb = loadTexture(renderer, "./resources/cell_redBomb.bmp");

    textures.numbers[1] = loadTexture(renderer, "./resources/one.bmp");
    textures.numbers[2] = loadTexture(renderer, "./resources/two.bmp");
    textures.numbers[3] = loadTexture(renderer, "./resources/three.bmp");
    textures.numbers[4] = loadTexture(renderer, "./resources/four.bmp");

    textures.plus = loadTexture(renderer, "./resources/plus.bmp");

    textures.player = loadTexture(renderer, "./resources/player.bmp");
    textures.bot = loadTexture(renderer, "./resources/bot.bmp");
    textures.restart = loadTexture(renderer, "./resources/restart.bmp");
}

void setBack(int x, int y, SDL_Renderer* renderer, SDL_Texture* image)
{
	int imageWidth, imageHeight;
	SDL_QueryTexture(image, NULL, NULL, &imageWidth, &imageHeight);
	SDL_Rect dstRect = { x, y, imageWidth, imageHeight };
	SDL_RenderCopy(renderer, image, NULL, &dstRect);
}

void loadImage(int x, int y, int sizeX, int sizeY,
               SDL_Renderer* renderer, SDL_Texture* image)
{
    SDL_Rect dstRect = { x, y, sizeX, sizeY };
    SDL_RenderCopy(renderer, image, NULL, &dstRect);
}
