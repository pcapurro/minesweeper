#include "header.h"

void	generateMap(tInfos* infos, const int xAvoid, const int yAvoid)
{
	int newY = getRandomNumber() % infos->height;
	int	newX = getRandomNumber() % infos->width;

	for (int i = 0; i != infos->bombs; i++)
	{
		while (infos->map[newY][newX].bomb == true
			|| (newY >= yAvoid - 1 && newY <= yAvoid + 1
				&& newX >= xAvoid - 1 && newX <= xAvoid + 1))
		{
			newY = getRandomNumber() % infos->height;
			newX = getRandomNumber() % infos->width;
		}

		infos->map[newY][newX].bomb = true;

		int nb = getRandomNumber() % 3;
		if (nb == 0 || nb == 1)
			infos->map[newY][newX].bombType = BOMB1;
		else
			infos->map[newY][newX].bombType = BOMB2;
	}

	for (int y = 0; infos->map[y] != NULL; y++)
	{
		for (int x = 0; x != infos->width; x++)
		{
			if (infos->map[y][x].bomb != true)
				infos->map[y][x].value = getBombsNumber(infos, y, x);
		}
	}
}

void	initializeMap(tInfos* infos)
{
	infos->map = malloc(sizeof(tCell*) * (infos->height + 1));

	if (!infos->map)
		endError(infos, 2);

	for (int y = 0; y != infos->height + 1; y++)
		infos->map[y] = NULL;

	for (int y = 0; y != infos->height; y++)
	{
		infos->map[y] = malloc(sizeof(tCell) * (infos->width));

		if (!infos->map[y])
		{
			infos->map[y] = NULL;

			for (int x = y - 1; x != -1; x--)
			{
				if (infos->map[y] != NULL)
					free(infos->map[y]), infos->map[y] = NULL;
			}
			endError(infos, 2);
		}

		for (int x = 0; x != infos->width; x++)
		{
			infos->map[y][x].discovered = false;
			infos->map[y][x].flag = false;

			infos->map[y][x].bomb = false;
			infos->map[y][x].bombType = BOMB1;

			infos->map[y][x].value = 0;
		}
	}

	infos->bombs = (infos->bombs * (infos->width * infos->height)) / 100;
	infos->flags = infos->bombs;
}

tColor	getColor(const int value)
{
	tColor	color = {0, 0, 0, 255};

	if (value == 1)
		color.r = 0, color.g = 0, color.b = 255;
	else if (value == 2)
		color.r = 0, color.g = 128, color.b = 0;
	else if (value == 3)
		color.r = 255, color.g = 0, color.b = 0;
	else if (value == 4)
		color.r = 0, color.g = 0, color.b = 128;
	else if (value == 5)
		color.r = 128, color.g = 0, color.b = 0;
	else if (value == 6)
		color.r = 0, color.g = 128, color.b = 128;
	else if (value == 7)
		color.r = 0, color.g = 0, color.b = 0;
	else if (value == 8)
		color.r = 128, color.g = 128, color.b = 128;
	else
		color.r = 0, color.g = 0, color.b = 0;
	
	return color;
}

void	loadTextureColors(SDL_Surface* surface, const int number)
{
	Uint32*	pixels = (Uint32*)surface->pixels;
	int		pixelTotal = surface->w * surface->h;
	tColor	color = getColor(number);

	for (int i = 0; i != pixelTotal; i++)
	{
		Uint8	r, g, b, a;

		SDL_GetRGBA(pixels[i], surface->format, &r, &g, &b, &a);

		if (a != 0)
			pixels[i] = SDL_MapRGBA(surface->format, color.r, color.g, color.b, a);
	}
}

SDL_Texture*	loadTexture(tInfos* infos, const char* path, const int number, const bool color)
{
	SDL_Surface*	surface = NULL;
	SDL_Texture*	texture = NULL;

	surface = SDL_LoadBMP(path);

	if (surface == NULL)
		endError(infos, 1);
	else
	{
		if (number != -1 && color == true)
		{
			SDL_Surface*	recoloredSurface = NULL;

			recoloredSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
			SDL_FreeSurface(surface);

			if (recoloredSurface == NULL)
				endError(infos, 1);

			loadTextureColors(recoloredSurface, number);

			texture = SDL_CreateTextureFromSurface(infos->mainRenderer, recoloredSurface);
			SDL_FreeSurface(recoloredSurface);
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(infos->mainRenderer, surface);
			SDL_FreeSurface(surface);
		}

		if (texture == NULL)
			endError(infos, 1);
	}

	return texture;
}

void	initializeTextures(tInfos* infos)
{
	infos->path = strDup("./materials/numbers/?.bmp");

	if (infos->path == NULL)
		endError(infos, 0);

	for (int i = 0; i != 9; i++)
	{
		infos->path[20] = i + 48;

		infos->textures.numbersColored[i] = loadTexture(infos, infos->path, i, true);
		infos->textures.numbers[i] = loadTexture(infos, infos->path, i, false);
	}

	infos->path[20] = 9 + 48;
	infos->textures.numbers[9] = loadTexture(infos, infos->path, 9, false);

	infos->textures.bomb1 = loadTexture(infos, "./materials/icons/bomb-1.bmp", -1, false);
	infos->textures.bomb2 = loadTexture(infos, "./materials/icons/bomb-2.bmp", -1, false);

	infos->textures.flag = loadTexture(infos, "./materials/icons/flag.bmp", -1, false);

	infos->textures.timer = loadTexture(infos, "./materials/icons/timer.bmp", -1, false);
	infos->textures.second = loadTexture(infos, "./materials/icons/second.bmp", -1, false);

	infos->textures.arrow = loadTexture(infos, "./materials/icons/arrow.bmp", -1, false);
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
