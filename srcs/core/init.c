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
	if (i != 0 && infos->map[i - 1][k + 1].bomb == true)
		value++;

	if (infos->map[i + 1] != NULL && k != 0 && infos->map[i + 1][k - 1].bomb == true)
		value++;
	if (infos->map[i + 1] != NULL && infos->map[i + 1][k + 1].bomb == true)
		value++;
	
	if (value == 0)
		return (-16);

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
				infos->map[i][k].value = getBombsNumber(infos, i, k) + 48;
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
		infos->map[i] = malloc(sizeof(tCell) * (infos->width + 1));
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
		else
		{
			for (int k = 0; k != infos->width; k++)
				infos->map[i][k].bomb = false;
		}
	}

	generateMap(infos);
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

	infos->normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	infos->interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (infos->normalCursor == NULL || infos->interactCursor == NULL)
		endError(infos, 1);
}
