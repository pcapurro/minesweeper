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

			SDL_SetRenderDrawColor(infos->mainRenderer, getRandomNumber(), getRandomNumber(), getRandomNumber(), 255);
			SDL_RenderFillRect(infos->mainRenderer, &obj);

			SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);
		}
		obj.y = 60 + (i * obj.h);
	}
}

void	displayGame(tInfos* infos)
{
	SDL_Rect	obj;

	obj.w = infos->width;
	obj.h = infos->height;

	SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(infos->mainRenderer, &obj);

	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);

	displayMap(infos);

	SDL_RenderPresent(infos->mainRenderer);
}
