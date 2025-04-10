#include "header.h"

void	drawBackground(tInfos* infos)
{
	SDL_Rect	obj;

	obj.x = 0, obj.y = 0;
	obj.w = (infos->width + 1) * 42;
	obj.h = (infos->height + 2) * 42;

	SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(infos->mainRenderer, &obj);
	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);

	obj.x = 16, obj.y = 65;
	obj.w = (infos->width * 42) + 10;
	obj.h = (infos->height * 42) + 10;

	SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(infos->mainRenderer, &obj);

	obj.x += 5, obj.y += 5;
	obj.w -= 10, obj.h -= 10;

	SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(infos->mainRenderer, &obj);

	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);
}

void	drawCell(tInfos* infos, SDL_Rect* obj, const int x, const int y)
{
	SDL_Rect	newObj;
	
	if (infos->map[x][y].discovered == false)
		SDL_SetRenderDrawColor(infos->mainRenderer, 128, 128, 128, 21);
	else
		SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);

	if (infos->map[x][y].flag == true)
	{
		SDL_Texture* texture = getTexture(infos, 84);

		newObj.w = 32 * (infos->width / 16), newObj.h = 32 * (infos->height / 16);

		newObj.x = obj->x + ((obj->w / 2) - (newObj.w / 2));
		newObj.y = obj->y + obj->h / 2 - (newObj.h / 2);

		SDL_RenderCopy(infos->mainRenderer, texture, NULL, &newObj);
	}

	SDL_RenderFillRect(infos->mainRenderer, obj);
	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, obj);

	if (infos->map[x][y].discovered == false)
		return ;

	if (infos->map[x][y].bomb == true)
	{
		SDL_Texture* texture = NULL;
		
		if (infos->map[x][y].bombType == 0)
			texture = getTexture(infos, 21);
		else
			texture = getTexture(infos, 42);

		newObj.w = 32 * (infos->width / 16), newObj.h = 32 * (infos->height / 16);

		newObj.x = obj->x + ((obj->w / 2) - (newObj.w / 2));
		newObj.y = obj->y + obj->h / 2 - (newObj.h / 2);

		SDL_RenderCopy(infos->mainRenderer, texture, NULL, &newObj);
	}
	else
	{
		SDL_Texture* texture = NULL;

		texture = getTexture(infos, infos->map[x][y].value);
		if (texture == NULL) {
			SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(infos->mainRenderer, obj);
		}

		newObj.w = 21 * (infos->width / 16), newObj.h = 52 * (infos->height / 16);

		newObj.x = obj->x + ((obj->w / 2) - (newObj.w / 2));
		newObj.y = obj->y + obj->h / 2 - (newObj.h / 2);

		SDL_RenderCopy(infos->mainRenderer, texture, NULL, &newObj);
	}
}

void	drawMap(tInfos* infos)
{
	SDL_Rect	obj;

	obj.x = 21;
	obj.y = 70;

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			obj.w = (infos->width * 42) / infos->width;
			obj.h = (infos->height * 42) / infos->height;

			obj.x = 21 + (k * obj.w);

			drawCell(infos, &obj, i, k);
		}
		obj.y = 70 + ((i + 1) * obj.h);
	}
}

void	displayGame(tInfos* infos)
{
	drawBackground(infos);
	drawMap(infos);

	SDL_RenderPresent(infos->mainRenderer);
}
