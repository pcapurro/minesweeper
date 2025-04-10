#include "header.h"

void	startGame(tInfos* infos)
{
	int			x = 0, y = 0;
	SDL_Event	event;

	displayGame(infos);

	while (true)
	{
		if (SDL_PollEvent(&event) == true)
		{
			if (event.type == SDL_QUIT \
				|| (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				return ;

			x = event.button.x;
			y = event.button.y;

			if (x > infos->width * 42 || y > infos->height * 42 || x < 0 || y < 0)
				continue ;

			sortEvent(infos, &event);

			displayGame(infos);

			usleep(250);
		}
	}
}
