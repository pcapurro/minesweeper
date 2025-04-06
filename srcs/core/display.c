#include "header.h"

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

			// SDL_SetRenderDrawColor(infos->mainRenderer, getRandomNumber() % 256, getRandomNumber() % 256, getRandomNumber() % 256, 255);

			if (infos->theme == 1)
				SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
			else
				SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);

			SDL_RenderFillRect(infos->mainRenderer, &obj);
			SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);
		}
		obj.y = 84 + (i * obj.h);
	}
}

void	displayGame(tInfos* infos)
{
	SDL_Rect	obj;

	obj.w = (infos->width + 1) * 42;
	obj.h = (infos->height + 2) * 42;

	if (infos->theme == 1)
		SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);
	else
		SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);

	SDL_RenderFillRect(infos->mainRenderer, &obj);

	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);

	displayMap(infos);

	SDL_RenderPresent(infos->mainRenderer);

	// for (int i = 0; infos->map[i] != NULL; i++)
	// 	printf("'%s'\n", infos->map[i]);
	// printf("\n");
}
