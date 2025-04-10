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
	SDL_Rect	cellObj;
	SDL_Rect	textObj;

	cellObj.x = 21;
	cellObj.y = 70;

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			cellObj.w = (infos->width * 42) / infos->width;
			cellObj.h = (infos->height * 42) / infos->height;

			cellObj.x = 21 + (k * cellObj.w);

			if (infos->map[i][k].bomb == false && infos->map[i][k].value == 0)
				continue ;

			SDL_Texture* texture = NULL;

			if (infos->map[i][k].bomb == true)
			{
				SDL_SetRenderDrawColor(infos->mainRenderer, 255, 0, 0, 255);
				SDL_RenderFillRect(infos->mainRenderer, &cellObj);

				SDL_RenderCopy(infos->mainRenderer, texture, NULL, &cellObj);
			}
			else
			{
				texture = getTexture(infos, infos->map[i][k].value);

				textObj.w = 21 * (infos->width / 16), textObj.h = 52 * (infos->height / 16);

				textObj.x = cellObj.x + ((cellObj.w / 2) - (textObj.w / 2));
				textObj.y = cellObj.y + cellObj.h / 2 - (textObj.h / 2);

				SDL_RenderCopy(infos->mainRenderer, texture, NULL, &textObj);
			}
		}
		cellObj.y = 70 + ((i + 1) * cellObj.h);
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
