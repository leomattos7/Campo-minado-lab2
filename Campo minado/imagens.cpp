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
    textures.tabuleiro = loadTexture(renderer, "tabuleiro.bmp");
    textures.celula = loadTexture(renderer, "cell.bmp");
    textures.bomba = loadTexture(renderer, "cell_bomba.bmp");
    textures.bandeira = loadTexture(renderer, "cell_flag.bmp");
    textures.celulaAberta = loadTexture(renderer, "cell_open.bmp");
    textures.score = loadTexture(renderer, "score.bmp");

    textures.numeros[1] = loadTexture(renderer, "one.bmp");
    textures.numeros[2] = loadTexture(renderer, "two.bmp");
    textures.numeros[3] = loadTexture(renderer, "three.bmp");
    textures.numeros[4] = loadTexture(renderer, "four.bmp");
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
