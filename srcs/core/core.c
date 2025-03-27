#include "header.h"

void	initializeGame(tInfos* infos)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		endError(infos, 1);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	infos->mainWindow = SDL_CreateWindow("minesweeper", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, infos->width, infos->height, 0);
	if (infos->mainWindow == NULL)
		endError(infos, 1);

	infos->mainRenderer = SDL_CreateRenderer(infos->mainWindow, -1, SDL_RENDERER_ACCELERATED);
	if (infos->mainRenderer == NULL)
		endError(infos, 1);

	SDL_SetRenderDrawBlendMode(infos->mainRenderer, SDL_BLENDMODE_BLEND);

	infos->normalCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	infos->interactCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

	if (infos->normalCursor == NULL || infos->interactCursor == NULL)
		endError(infos, 1);
}

void	startGame(tInfos* infos)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	while (true)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ;

			x = event.button.x;
			y = event.button.y;

			if (x > infos->width || y > infos->height || x < 0 || y < 0)
				continue ;

			sortEvent(infos, &event);

			displayGame(infos);

			usleep(250);
		}
	}
}
