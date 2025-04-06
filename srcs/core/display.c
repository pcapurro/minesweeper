#include "header.h"

SDL_Texture*	getTexture(tInfos* infos, const int value)
{
	if (value == 1)
		return (infos->one);
	if (value == 2)
		return (infos->two);
	if (value == 3)
		return (infos->three);
	if (value == 4)
		return (infos->four);

	if (value == 5)
		return (infos->five);
	if (value == 6)
		return (infos->six);
	if (value == 7)
		return (infos->seven);
	if (value == 8)
		return (infos->eight);

	return (NULL);
}

void	displayMap(tInfos* infos)
{
	SDL_Rect	obj;

	obj.x = 21;
	obj.y = 84;

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			obj.w = (infos->width * 42) / infos->width;
			obj.h = (infos->height * 42) / infos->height;

			obj.x = 21 + (k * obj.w);

			if (infos->map[i][k].value != -1)
				SDL_RenderCopy(infos->mainRenderer, getTexture(infos, infos->map[i][k].value), NULL, &obj);
			else
			{
				SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
				SDL_RenderFillRect(infos->mainRenderer, &obj);
				SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);
			}
		}
		obj.y = 84 + (i * obj.h);
	}
}

void	displayGame(tInfos* infos)
{
	SDL_Rect	obj;

	obj.w = (infos->width + 1) * 42;
	obj.h = (infos->height + 2) * 42;

	SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);

	SDL_RenderFillRect(infos->mainRenderer, &obj);

	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);

	displayMap(infos);

	SDL_RenderPresent(infos->mainRenderer);
}
