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

	if (infos->textures.one != NULL)
		SDL_DestroyTexture(infos->textures.one);
	if (infos->textures.two != NULL)
		SDL_DestroyTexture(infos->textures.two);
	if (infos->textures.three != NULL)
		SDL_DestroyTexture(infos->textures.three);
	if (infos->textures.four != NULL)
		SDL_DestroyTexture(infos->textures.four);

	if (infos->textures.five != NULL)
		SDL_DestroyTexture(infos->textures.five);
	if (infos->textures.six != NULL)
		SDL_DestroyTexture(infos->textures.six);
	if (infos->textures.seven != NULL)
		SDL_DestroyTexture(infos->textures.seven);
	if (infos->textures.eight != NULL)
		SDL_DestroyTexture(infos->textures.eight);

	if (infos->textures.bomb1 != NULL)
		SDL_DestroyTexture(infos->textures.bomb1);
	if (infos->textures.bomb2 != NULL)
		SDL_DestroyTexture(infos->textures.bomb2);

	if (infos->textures.flag != NULL)
		SDL_DestroyTexture(infos->textures.flag);
	if (infos->textures.clock != NULL)
		SDL_DestroyTexture(infos->textures.clock);

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

	exit(1);
}
