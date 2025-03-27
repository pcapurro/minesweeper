#include "header.h"

void	displayGame(tInfos* infos)
{
	SDL_Rect	obj;

	obj.w = infos->width;
	obj.h = infos->height;

	SDL_SetRenderDrawColor(infos->mainRenderer, 0, 0, 0, 255);
	SDL_RenderFillRect(infos->mainRenderer, &obj);

	SDL_RenderCopy(infos->mainRenderer, NULL, NULL, &obj);

	SDL_RenderPresent(infos->mainRenderer);
}
