#include "header.h"

void	endError(tInfos* infos, const int value)
{
	if (value == 0)
		writeStr("Error! Memory failed.\n", 2);
	else if (value == 1)
		writeStr("Error! SDL failed.\n", 2);

	endFree(infos);
}

void	endFree(tInfos* infos)
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

	if (infos->mainRenderer != NULL)
		SDL_DestroyRenderer(infos->mainRenderer);

	if (infos->mainWindow != NULL)
		SDL_DestroyWindow(infos->mainWindow);

	if (infos->normalCursor != NULL)
		SDL_FreeCursor(infos->normalCursor);
	if (infos->interactCursor != NULL)
		SDL_FreeCursor(infos->interactCursor);

	SDL_Quit();
}
