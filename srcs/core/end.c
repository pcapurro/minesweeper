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

	if (infos->one != NULL)
		SDL_DestroyTexture(infos->one);
	if (infos->two != NULL)
		SDL_DestroyTexture(infos->two);
	if (infos->three != NULL)
		SDL_DestroyTexture(infos->three);
	if (infos->four != NULL)
		SDL_DestroyTexture(infos->four);

	if (infos->five != NULL)
		SDL_DestroyTexture(infos->five);
	if (infos->six != NULL)
		SDL_DestroyTexture(infos->six);
	if (infos->seven != NULL)
		SDL_DestroyTexture(infos->seven);
	if (infos->eight != NULL)
		SDL_DestroyTexture(infos->eight);

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
