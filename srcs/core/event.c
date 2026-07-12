#include "header.h"

void	discoverZone(tInfos* infos, const int x, const int y)
{
	if (infos->map[y][x].discovered == false)
		infos->map[y][x].discovered = true;

	if (infos->map[y][x].value != 0)
		return;

	int value = 0;

	int	xCoords[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int	yCoords[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

	for (int y = 0; infos->map[y] != NULL; y++)
	{
		for (int x = 0; x != infos->width; x++)
		{
			if (infos->map[y][x].discovered == false || infos->map[y][x].value != 0)
				continue;

			for (int l = 0; l != 8; l++)
			{
				int newX = y + xCoords[l];
				int newY = x + yCoords[l];

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
	for (int y = 0; infos->map[y] != NULL; y++)
	{
		for (int x = 0; x != infos->width; x++)
		{
			if (infos->map[y][x].discovered == false)
				infos->map[y][x].discovered = true;
		}
	}
}

void	reactEvent(tInfos* infos, const int x, const int y, const int event)
{
	if (event == SDL_BUTTON_LEFT)
	{
		if (infos->map[y][x].flag == true)
			return;

		if (infos->moves == 0)
			generateMap(infos, x, y);

		infos->moves++;

		if (infos->map[y][x].flag == true)
			infos->map[y][x].flag = false, infos->flags++;

		if (infos->over == true || infos->map[y][x].bomb == true)
		{
			discoverMap(infos);

			infos->over = true;
			infos->finalTime = getTime();

			infos->xHighLight = -1;
			infos->yHighLight = -1;

			displayGame(infos);

			printf("%sYou lost the game.%s\n", RED, COLOR_E);
			printf("Time: %lds.\n", (infos->finalTime - infos->startTime) / 1000);

			return;
		}
		else
			discoverZone(infos, x, y);
	}

	if (event == SDL_BUTTON_RIGHT)
	{
		if (infos->map[y][x].flag == true)
			infos->map[y][x].flag = false, infos->flags++;

		else if (infos->flags > 0)
			infos->map[y][x].flag = true, infos->flags--;
	}

	if (event == SDL_MOUSEMOTION)
	{
		infos->xHighLight = -1, infos->yHighLight = -1;

		if (infos->map[y][x].discovered == false)
			infos->xHighLight = x, infos->yHighLight = y;
	}
}

void	sortEvent(tInfos* infos, SDL_Event* event)
{
	int		x = -1;
	int		y = -1;

	bool	motion = false;
	bool	click = false;

	if (event->type == SDL_KEYDOWN \
		&& event->key.keysym.sym == SDLK_RETURN)
		resetGame(infos);

	if (event->type == SDL_MOUSEMOTION)
		motion = true;
	else if (event->type == SDL_MOUSEBUTTONUP)
		click = true;

	if (click == true)
	{
		x = event->button.x;
		y = event->button.y;
		
		if (isResetZone(infos, x, y) == true)
			resetGame(infos);

		if (infos->over == false && checkCoords(infos, x, y) == true)
		{
			int	tX = translateCoords(infos, x, y, 'x');
			int	tY = translateCoords(infos, x, y, 'y');

			if (event->button.button == SDL_BUTTON_LEFT)
				reactEvent(infos, tX, tY, SDL_BUTTON_LEFT);
			else if (event->button.button == SDL_BUTTON_RIGHT
				&& infos->map[tY][tX].discovered == false)
				reactEvent(infos, tX, tY, SDL_BUTTON_RIGHT);
		}

	}
	
	if (motion == true)
	{
		x = event->motion.x;
		y = event->motion.y;

		if (isResetZone(infos, x, y) == true)
			SDL_SetCursor(infos->interactCursor);
		else
			SDL_SetCursor(infos->normalCursor);

		if (infos->over == false && checkCoords(infos, x, y) == true)
		{
			int	tX = translateCoords(infos, x, y, 'x');
			int	tY = translateCoords(infos, x, y, 'y');

			reactEvent(infos, tX, tY, SDL_MOUSEMOTION);
		}
		else if (infos->xHighLight != -1 || infos->yHighLight != -1)
			infos->xHighLight = -1, infos->xHighLight = -1;
	}
}
