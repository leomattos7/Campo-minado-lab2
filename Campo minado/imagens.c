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
    textures.board = loadTexture(renderer, "tabuleiro.bmp");
    textures.cell[0] = loadTexture(renderer, "cell_oGreen.bmp");
    textures.cell[1] = loadTexture(renderer, "cell_oBlue.bmp");
    textures.bomb = loadTexture(renderer, "cell_bomba.bmp");
    textures.flag = loadTexture(renderer, "cell_flag.bmp");
    textures.openCell = loadTexture(renderer, "cell_open.bmp");
    textures.score = loadTexture(renderer, "score.bmp");
    textures.redBomb = loadTexture(renderer, "cell_redBomb.bmp");

    textures.numbers[1] = loadTexture(renderer, "one.bmp");
    textures.numbers[2] = loadTexture(renderer, "two.bmp");
    textures.numbers[3] = loadTexture(renderer, "three.bmp");
    textures.numbers[4] = loadTexture(renderer, "four.bmp");

    textures.plus = loadTexture(renderer, "plus.bmp");
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
