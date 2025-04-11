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
			infos->map[i][k].bombType = 0;

			infos->map[i][k].value = 0;

			infos->map[i][k].discovered = false;
			infos->map[i][k].flag = false;
		}
	}

	generateMap(infos);

	infos->flags = infos->bombs;
}

void	startGame(tInfos* infos)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	while (true)
	{
		if (infos->over == false && isOver(infos) == true)
		{
			printf(GREEN);
			printf("You won the game! 🎉\n");
			printf(COLOR_E);

			infos->over = true;
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
