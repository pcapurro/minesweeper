#include "header.h"

void	generateMap(tInfos* infos)
{
	int value1 = getRandomNumber() % infos->height;
	int	value2 = getRandomNumber() % infos->width;

	for (int i = infos->bombs; i != 0; i--)
	{
		while (infos->map[value1][value2].bomb == true)
		{
			value1 = getRandomNumber() % infos->height;
			value2 = getRandomNumber() % infos->width;
		}

		infos->map[value1][value2].bomb = true;

		int nb = getRandomNumber() % 3;
		if (nb == 0 || nb == 1)
			infos->map[value1][value2].bombType = BOMB1;
		else
			infos->map[value1][value2].bombType = BOMB2;
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

			infos->map[i][k].bomb = false;
			infos->map[i][k].bombType = BOMB1;

			infos->map[i][k].value = 0;
		}
	}

	infos->bombs = (infos->bombs * (infos->width * infos->height)) / 100;
	infos->flags = infos->bombs;

	generateMap(infos);
}

SDL_Texture* loadTexture(tInfos* infos, const char* path)
{
	SDL_Surface*	surface = NULL;
	SDL_Texture*	texture = NULL;

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
	infos->textures.zero = loadTexture(infos, "./materials/numbers/0.bmp");
	infos->textures.one = loadTexture(infos, "./materials/numbers/1.bmp");
	infos->textures.two = loadTexture(infos, "./materials/numbers/2.bmp");
	infos->textures.three = loadTexture(infos, "./materials/numbers/3.bmp");
	infos->textures.four = loadTexture(infos, "./materials/numbers/4.bmp");

	infos->textures.five = loadTexture(infos, "./materials/numbers/5.bmp");
	infos->textures.six = loadTexture(infos, "./materials/numbers/6.bmp");
	infos->textures.seven = loadTexture(infos, "./materials/numbers/7.bmp");
	infos->textures.eight = loadTexture(infos, "./materials/numbers/8.bmp");
	infos->textures.nine = loadTexture(infos, "./materials/numbers/9.bmp");

	infos->textures.bomb1 = loadTexture(infos, "./materials/icons/bomb-1.bmp");
	infos->textures.bomb2 = loadTexture(infos, "./materials/icons/bomb-2.bmp");

	infos->textures.flag = loadTexture(infos, "./materials/icons/flag.bmp");

	infos->textures.timer = loadTexture(infos, "./materials/icons/timer.bmp");
	infos->textures.second = loadTexture(infos, "./materials/icons/second.bmp");

	infos->textures.arrow = loadTexture(infos, "./materials/icons/arrow.bmp");
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
