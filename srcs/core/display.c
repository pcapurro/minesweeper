#include "header.h"

SDL_Texture*	getTexture(tInfos* infos, const int value)
{
	if (value == 1)
		return (infos->textures.one);
	if (value == 2)
		return (infos->textures.two);
	if (value == 3)
		return (infos->textures.three);
	if (value == 4)
		return (infos->textures.four);

	if (value == 5)
		return (infos->textures.five);
	if (value == 6)
		return (infos->textures.six);
	if (value == 7)
		return (infos->textures.seven);
	if (value == 8)
		return (infos->textures.eight);

	if (value == 21)
		return (infos->textures.bomb1);
	if (value == 42)
		return (infos->textures.bomb2);

	if (value == 84)
		return (infos->textures.flag);
	if (value == 128)
		return (infos->textures.clock);

	if (value == 256)
		return (infos->textures.arrow);

	return (NULL);
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
	SDL_Rect	textObj;

	if (infos->map[x][y].flag == true && infos->over == false)
		SDL_SetRenderDrawColor(infos->mainRenderer, 121, 0, 0, 21);
	else
		SDL_SetRenderDrawColor(infos->mainRenderer, 255, 255, 255, 255);

	SDL_RenderFillRect(infos->mainRenderer, obj);
	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, obj);

	if (infos->map[x][y].discovered == false)
		return ;

	SDL_Texture* texture = NULL;

	if (infos->map[x][y].bomb == true)
	{
		SDL_SetRenderDrawColor(infos->mainRenderer, 255, 0, 0, 255);
		SDL_RenderFillRect(infos->mainRenderer, obj);
		SDL_RenderCopy(infos->mainRenderer, NULL, NULL, obj);
	}
	else
	{
		texture = getTexture(infos, infos->map[x][y].value);
		if (texture == NULL) {
			SDL_SetRenderDrawColor(infos->mainRenderer, 128, 128, 128, 21);
			SDL_RenderFillRect(infos->mainRenderer, obj);
		}

		textObj.w = 21 * (infos->width / 16), textObj.h = 52 * (infos->height / 16);

		textObj.x = obj->x + ((obj->w / 2) - (textObj.w / 2));
		textObj.y = obj->y + obj->h / 2 - (textObj.h / 2);

		SDL_RenderCopy(infos->mainRenderer, texture, NULL, &textObj);
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
