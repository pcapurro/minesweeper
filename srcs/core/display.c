#include "header.h"

void	displayMap(tInfos* infos)
{
	SDL_Rect	obj;

	obj.x = 15;
	obj.y = 60;

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; infos->map[i][k] != '\0'; k++)
		{
			obj.w = (infos->width * 30) / infos->width;
			obj.h = (infos->height * 30) / infos->height;

			obj.x = 15 + (k * obj.w);

			if (infos->theme == 1)
				SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
			else
				SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);

			SDL_RenderFillRect(infos->mainRenderer, &obj);
			SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);
		}
		obj.y = 60 + (i * obj.h);
	}
}

void	displayGame(tInfos* infos)
{
	SDL_Rect	obj;

	obj.w = (infos->width + 1) * 30;
	obj.h = (infos->height + 2) * 30;

	if (infos->theme == 1)
		SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);
	else
		SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(infos->mainRenderer, &obj);

	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);

	displayMap(infos);

	SDL_RenderPresent(infos->mainRenderer);
}
