#include "header.h"

void	endError(tInfos* infos, const int value)
{
	if (value == 0)
		writeStr("Error! Memory failed.\n", 2);
	else if (value == 1)
		writeStr("Error! SDL failed.\n", 2);

	endFree(infos, 1);
}

void	endFree(tInfos* infos, const int value)
{
	if (infos->map != NULL)
	{
		for (int i = 0; i != infos->height; i++)
		{
			if (infos->map[i] != NULL)
				free(infos->map[i]), infos->map[i] = NULL;
		}
		free(infos->map);
		infos->map = NULL;
	}

	if (infos->path != NULL)
		free(infos->path);

	for (int i = 0; i != 9; i++)
	{
		if (infos->textures.numbersColored[i] != NULL)
			SDL_DestroyTexture(infos->textures.numbersColored[i]);

		if (infos->textures.numbers[i] != NULL)
			SDL_DestroyTexture(infos->textures.numbers[i]);
	}

	if (infos->textures.numbers[9] != NULL)
		SDL_DestroyTexture(infos->textures.numbers[9]);

	if (infos->textures.bomb1 != NULL)
		SDL_DestroyTexture(infos->textures.bomb1);
	if (infos->textures.bomb2 != NULL)
		SDL_DestroyTexture(infos->textures.bomb2);

	if (infos->textures.flag != NULL)
		SDL_DestroyTexture(infos->textures.flag);
	if (infos->textures.timer != NULL)
		SDL_DestroyTexture(infos->textures.timer);

	if (infos->textures.arrow != NULL)
		SDL_DestroyTexture(infos->textures.arrow);

	if (infos->mainRenderer != NULL)
		SDL_DestroyRenderer(infos->mainRenderer);

	if (infos->mainWindow != NULL)
		SDL_DestroyWindow(infos->mainWindow);

	if (infos->normalCursor != NULL)
		SDL_FreeCursor(infos->normalCursor);
	if (infos->interactCursor != NULL)
		SDL_FreeCursor(infos->interactCursor);

	SDL_Quit();

	exit(value);
}
