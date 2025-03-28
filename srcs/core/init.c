#include "header.h"

void	generateMap(tInfos* infos)
{
	infos->bombs = (infos->bombs * (infos->width * infos->height)) / 100;

	for (int i = infos->bombs; i != -1; i--)
	{
		int value1 = getRandomNumber() % infos->height;
		int value2 = getRandomNumber() % infos->width;

		infos->map[value1][value2] = '1';
	}
}

void	initializeMap(tInfos* infos)
{
	infos->map = malloc(sizeof(char*) * (infos->height + 1));
	if (!infos->map)
		endError(infos, 2);
	for (int i = 0; i != infos->height + 1; i++)
		infos->map[i] = NULL;

	for (int i = 0; i != infos->height; i++)
	{
		infos->map[i] = malloc(sizeof(char) * (infos->width + 1));
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
				infos->map[i][k] = '0';
			infos->map[i][infos->width] = '\0';
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
		SDL_WINDOWPOS_CENTERED, (infos->width + 1) * 30, (infos->height + 2) * 30, 0);
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
