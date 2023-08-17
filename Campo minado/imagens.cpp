#include "imagens.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file)
{
    SDL_Surface* bitmap = SDL_LoadBMP(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
    return texture;
}

void setBack(int x, int y, SDL_Renderer* renderer, SDL_Texture* image)
{
	int imageWidth, imageHeight;
	SDL_QueryTexture(image, NULL, NULL, &imageWidth, &imageHeight);
	SDL_Rect dstRect = { x, y, imageWidth, imageHeight };
	SDL_RenderCopy(renderer, image, NULL, &dstRect);
}

void setImgFree(int x1, int x2, int y1, int y2,
                SDL_Renderer* renderer, SDL_Texture* image)
{
	SDL_Rect dstRect = { x1, y1, x2, y2 };
	SDL_RenderCopy(renderer, image, NULL, &dstRect);
}

void loadImage(int x, int y, int sizeX, int sizeY,
               SDL_Renderer* renderer, SDL_Texture* image)
{
    SDL_Rect dstRect = { x, y, sizeX, sizeY };
    SDL_RenderCopy(renderer, image, NULL, &dstRect);
}