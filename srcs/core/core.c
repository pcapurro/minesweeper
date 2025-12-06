#include "header.h"

void	resetGame(tInfos* infos)
{
	infos->over = false;
	infos->moves = 0;

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			infos->map[i][k].bomb = false;
			infos->map[i][k].bombType = BOMB1;

			infos->map[i][k].value = 0;

			infos->map[i][k].discovered = false;
			infos->map[i][k].flag = false;
		}
	}

	SDL_SetCursor(infos->normalCursor);

	infos->xHighLight = -1;
	infos->yHighLight = -1;

	infos->flags = infos->bombs;
	infos->startTime = getTime();
}

void	startGame(tInfos* infos)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	infos->startTime = getTime();

	while (true)
	{
		if (infos->over == false && isOver(infos) == true)
		{
			infos->over = true;
			infos->finalTime = getTime();

			infos->xHighLight = -1;
			infos->yHighLight = -1;

			printf("%sYou won the game! 🎉%s\n", GREEN, COLOR_E);
			printf("Time: %lds.\n", (infos->finalTime - infos->startTime) / 1000);
		}

		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ;

			x = event.button.x;
			y = event.button.y;

			if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN \
				|| event.type == SDL_MOUSEBUTTONUP)
			{
				if (x > (infos->width + 1) * 42 || y > (infos->height + 2) * 42 || x < 0 || y < 0)
					continue ;
			}

			sortEvent(infos, &event);
		}

		displayGame(infos);

		usleep(250);
	}
}
