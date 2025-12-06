#include "header.h"

void	discoverZone(tInfos* infos, const int x, const int y)
{
	if (infos->map[x][y].discovered == false)
		infos->map[x][y].discovered = true;

	if (infos->map[x][y].value != 0)
		return;

	int value = 0;

	int	xCoords[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int	yCoords[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			if (infos->map[i][k].discovered == false || infos->map[i][k].value != 0)
				continue;

			for (int l = 0; l != 8; l++)
			{
				int newX = i + xCoords[l];
				int newY = k + yCoords[l];

				if (newX >= 0 && newX < infos->height
					&& newY >= 0 && newY < infos->width)
				{
					if (infos->map[newX][newY].discovered == false
						&& infos->map[newX][newY].bomb == false)
					{
						if (infos->map[newX][newY].flag == true)
							infos->flags++;
						infos->map[newX][newY].discovered = true;

						if (infos->map[newX][newY].value == 0)
							value++;
					}
				}
			}
		}
	}

	if (value != 0)
		discoverZone(infos, x, y);
}

void	discoverMap(tInfos* infos)
{
	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			if (infos->map[i][k].discovered == false)
				infos->map[i][k].discovered = true;
		}
	}
}

void	reactEvent(tInfos* infos, const int x, const int y, const int event)
{
	if (event == SDL_BUTTON_LEFT)
	{
		if (infos->map[x][y].flag == true)
			return;

		if (infos->moves == 0)
			generateMap(infos, x, y);

		infos->moves++;

		if (infos->map[x][y].flag == true)
			infos->map[x][y].flag = false, infos->flags++;

		if (infos->over == true || infos->map[x][y].bomb == true)
		{
			discoverMap(infos);

			infos->over = true;
			infos->finalTime = getTime();

			infos->xHighLight = -1;
			infos->yHighLight = -1;

			printf("%sYou lost the game.%s\n", RED, COLOR_E);
			printf("Time: %lds.\n\n", (infos->finalTime - infos->startTime) / 1000);

			return ;
		}
		else
			discoverZone(infos, x, y);
	}

	if (event == SDL_BUTTON_RIGHT)
	{
		if (infos->map[x][y].flag == true)
			infos->map[x][y].flag = false, infos->flags++;
		else if (infos->flags > 0)
			infos->map[x][y].flag = true, infos->flags--;
	}

	if (event == SDL_MOUSEMOTION)
	{
		if (infos->map[x][y].discovered == false)
			infos->xHighLight = x, infos->yHighLight = y;
		else
			infos->xHighLight = -1, infos->yHighLight = -1;
	}
}

void	sortEvent(tInfos* infos, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN \
		&& event->key.keysym.sym == SDLK_RETURN)
		resetGame(infos);

	if (event->type == SDL_MOUSEBUTTONUP || event->type == SDL_MOUSEMOTION)
	{
		if (infos->over == false \
			&& checkCoords(infos, event->button.x, event->button.y) == true)
		{
			int x = translateCoords(infos, event->button.x, event->button.y, 0);
			int y = translateCoords(infos, event->button.x, event->button.y, 1);

			if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_LEFT)
				reactEvent(infos, x, y, SDL_BUTTON_LEFT);

			if (event->type == SDL_MOUSEBUTTONUP && event->button.button == SDL_BUTTON_RIGHT \
				&& infos->map[x][y].discovered == false)
				reactEvent(infos, x, y, SDL_BUTTON_RIGHT);

			if (event->type == SDL_MOUSEMOTION)
				reactEvent(infos, x, y, SDL_MOUSEMOTION);
		}
	}

	if (event->button.y > 9 && event->button.y <= 60 \
		&& event->button.x >= (((infos->width + 1) * 42) - 21 - (45 * (infos->width / 16))) \
		&& event->button.x <= ((infos->width + 1) * 42) - 28)
	{
		SDL_SetCursor(infos->interactCursor);

		if (event->type == SDL_MOUSEBUTTONUP)
			resetGame(infos);
	}
	else
		SDL_SetCursor(infos->normalCursor);

	displayGame(infos);
}
