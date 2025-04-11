#include "header.h"

void	drawLines(tInfos* infos)
{
	SDL_Rect	obj;

	obj.y = 70;
	obj.w = 2;

	for (int i = 1; i != infos->width; i++)
	{
		obj.h = (infos->height * 42);
		obj.x = 21 + (i * (infos->width * 42) / infos->width) - 1;

		SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
		SDL_RenderFillRect(infos->mainRenderer, &obj);

		SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);
	}

	obj.x = 21;
	obj.h = 2;

	for (int i = 0; i != infos->height; i++)
	{
		obj.w = (infos->width * 42);
		obj.y = 70 + ((i + 1) * (infos->height * 42) / infos->height);

		SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
		SDL_RenderFillRect(infos->mainRenderer, &obj);

		SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);
	}
}

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
	{
		SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 42);
		if (x == infos->xHighLight && y == infos->yHighLight)
			SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 121);
	}
	else
		SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);

	if (infos->map[x][y].flag == true)
	{
		SDL_Texture* texture = getTexture(infos, FLAG);

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
		
		if (infos->map[x][y].bombType == BOMB1)
			texture = getTexture(infos, BOMB1);
		else
			texture = getTexture(infos, BOMB2);

		newObj.w = 32 * (infos->width / 16), newObj.h = 32 * (infos->height / 16);

		newObj.x = obj->x + ((obj->w / 2) - (newObj.w / 2));
		newObj.y = obj->y + obj->h / 2 - (newObj.h / 2);

		SDL_RenderCopy(infos->mainRenderer, texture, NULL, &newObj);
	}
	else
	{
		SDL_Texture* texture = NULL;

		if (infos->map[x][y].value != 0)
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

void	drawFlags(tInfos* infos)
{
	SDL_Texture*	texture = NULL;
	SDL_Rect		obj;

	texture = getTexture(infos, FLAG);

	obj.x = 21;
	obj.y = 21;

	obj.w = 32 * (infos->width / 16), obj.h = 32 * (infos->height / 16);

	obj.x = obj.x + ((obj.w / 2) - (obj.w / 2));
	obj.y = obj.y + obj.h / 2 - (obj.h / 2);

	SDL_RenderCopy(infos->mainRenderer, texture, NULL, &obj);

	char	nb[3] = {0, 0, 0};
	snprintf(nb, sizeof(nb), "%d", infos->flags);

	obj.w = 19 * (infos->width / 16), obj.h = 50 * (infos->height / 16);
	obj.y = obj.y - (obj.w / 2);

	obj.x += 21;

	for (int i = 0; nb[i] != '\0'; i++)
	{
		obj.x += 21;
		texture = getTexture(infos, nb[i] - 48);

		SDL_RenderCopy(infos->mainRenderer, texture, NULL, &obj);
	}
}

void	drawTimer(tInfos* infos)
{
	SDL_Texture*	texture = NULL;
	SDL_Rect		obj;

	texture = getTexture(infos, TIMER);

	obj.x = 21 * 7;
	obj.y = 21;

	obj.w = 34 * (infos->width / 16), obj.h = 34 * (infos->height / 16);

	obj.x = obj.x + ((obj.w / 2) - (obj.w / 2));
	obj.y = obj.y + obj.h / 2 - (obj.h / 2);

	SDL_RenderCopy(infos->mainRenderer, texture, NULL, &obj);

	char	nb[21];

	for (int i = 0; i != 21; i++)
		nb[i] = '\0';

	if (infos->over == true)
		snprintf(nb, sizeof(nb), "%ld", (infos->finalTime - infos->startTime) / 1000);
	else
		snprintf(nb, sizeof(nb), "%ld", (getTime() - infos->startTime) / 1000);

	obj.w = 19 * (infos->width / 16), obj.h = 50 * (infos->height / 16);
	obj.y = obj.y - (obj.w / 2);

	obj.x += 21;

	for (int i = 0; nb[i] != '\0'; i++)
	{
		obj.x += 21;
		texture = getTexture(infos, nb[i] - 48);

		SDL_RenderCopy(infos->mainRenderer, texture, NULL, &obj);
	}
}

void	drawArrow(tInfos* infos)
{
	SDL_Texture*	texture = NULL;
	SDL_Rect		obj;

	texture = getTexture(infos, ARROW);

	obj.w = 45 * (infos->width / 16), obj.h = 45 * (infos->height / 16);

	obj.x = ((infos->width + 1) * 42) - 21 - obj.w;
	obj.y = 15;

	obj.x = obj.x + ((obj.w / 2) - (obj.w / 2));
	obj.y = obj.y + obj.h / 2 - (obj.h / 2);

	SDL_RenderCopy(infos->mainRenderer, texture, NULL, &obj);
}

void	displayGame(tInfos* infos)
{
	drawBackground(infos);
	drawMap(infos);
	drawLines(infos);

	drawFlags(infos);
	drawTimer(infos);

	drawArrow(infos);

	SDL_RenderPresent(infos->mainRenderer);
}
