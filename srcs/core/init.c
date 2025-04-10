#include "header.h"

int	getBombsNumber(tInfos* infos, const int i, const int k)
{
	int	value = 0;

	if (i != 0 && infos->map[i - 1][k].bomb == true)
		value++;
	if (infos->map[i + 1] != NULL && infos->map[i + 1][k].bomb == true)
		value++;

	if (k != 0 && infos->map[i][k - 1].bomb == true)
		value++;
	if (infos->map[i][k].bomb == true)
		value++;

	if (i != 0 && k != 0 && infos->map[i - 1][k - 1].bomb == true)
		value++;
	if (i != 0 && k + 1 != infos->width && infos->map[i - 1][k + 1].bomb == true)
		value++;

	if (infos->map[i + 1] != NULL && k != 0 && infos->map[i + 1][k - 1].bomb == true)
		value++;
	if (infos->map[i + 1] != NULL && k + 1 != infos->width && infos->map[i + 1][k + 1].bomb == true)
		value++;
	
	if (value == 0)
		return (-1);

	return (value);
}

void	generateMap(tInfos* infos)
{
	int value1 = getRandomNumber() % infos->height;
	int	value2 = getRandomNumber() % infos->width;

	infos->bombs = (infos->bombs * (infos->width * infos->height)) / 100;

	for (int i = infos->bombs; i != -1; i--)
	{
		while (infos->map[value1][value2].bomb == true)
		{
			value1 = getRandomNumber() % infos->height;
			value2 = getRandomNumber() % infos->width;
		}

		infos->map[value1][value2].bomb = true;
	}

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			if (infos->map[i][k].bomb != true)
				infos->map[i][k].value = getBombsNumber(infos, i, k);
		}
	}
}

void	initializeMap(tInfos* infos)
{
	infos->map = malloc(sizeof(tCell*) * (infos->height + 1));
	if (!infos->map)
		endError(infos, 2);
	for (int i = 0; i != infos->height + 1; i++)
		infos->map[i] = NULL;

	for (int i = 0; i != infos->height; i++)
	{
		infos->map[i] = malloc(sizeof(tCell) * (infos->width));
		if (!infos->map[i])
		{
			infos->map[i] = NULL;
			for (int k = i - 1; k != -1; k--)
			{
				if (infos->map[i] != NULL)
					free(infos->map[i]), infos->map[i] = NULL;
			}
			endError(infos, 2);
		}

		for (int k = 0; k != infos->width; k++)
		{
			infos->map[i][k].discovered = false;
			infos->map[i][k].flag = false;

			infos->map[i][k].value = 0;
			infos->map[i][k].bomb = false;
		}
	}

	generateMap(infos);
}

SDL_Texture* loadTexture(tInfos* infos, const char* path)
{
	SDL_Surface*	surface;
	SDL_Texture*	texture;

	surface = SDL_LoadBMP(path);
	if (surface == NULL)
		endError(infos, 1);
	else
	{
		texture = SDL_CreateTextureFromSurface(infos->mainRenderer, surface);
		SDL_FreeSurface(surface);
		if (texture == NULL)
			endError(infos, 1);
	}

	return (texture);
}

void	initializeTextures(tInfos* infos)
{
	infos->one = loadTexture(infos, "./materials/1.bmp");
	infos->two = loadTexture(infos, "./materials/2.bmp");
	infos->three = loadTexture(infos, "./materials/3.bmp");
	infos->four = loadTexture(infos, "./materials/4.bmp");

	infos->five = loadTexture(infos, "./materials/5.bmp");
	infos->six = loadTexture(infos, "./materials/6.bmp");
	infos->seven = loadTexture(infos, "./materials/7.bmp");
	infos->eight = loadTexture(infos, "./materials/8.bmp");
}

void	initializeDisplay(tInfos* infos)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		endError(infos, 1);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	infos->mainWindow = SDL_CreateWindow("minesweeper", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, (infos->width + 1) * 42, (infos->height + 2) * 42, 0);
	if (infos->mainWindow == NULL)
		endError(infos, 1);

	infos->mainRenderer = SDL_CreateRenderer(infos->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (infos->mainRenderer == NULL)
		endError(infos, 1);

	SDL_SetRenderDrawBlendMode(infos->mainRenderer, SDL_BLENDMODE_BLEND);

	initializeTextures(infos);

	infos->normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	infos->interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (infos->normalCursor == NULL || infos->interactCursor == NULL)
		endError(infos, 1);
}
