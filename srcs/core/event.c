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
		infos->xHighLight = -1, infos->yHighLight = -1;

		if (infos->map[x][y].discovered == false)
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
		
		if (infos->over == false && checkCoords(infos, x, y) == true)
		{
			int	tx = translateCoords(infos, x, y, 0);
			int	ty = translateCoords(infos, x, y, 1);

			if (event->button.button == SDL_BUTTON_LEFT)
				reactEvent(infos, tx, ty, SDL_BUTTON_LEFT);
			else if (event->button.button == SDL_BUTTON_RIGHT
				&& infos->map[tx][ty].discovered == false)
				reactEvent(infos, tx, ty, SDL_BUTTON_RIGHT);
		}

		if (isResetZone(infos, x, y) == true)
			resetGame(infos);
	}
	else if (motion == true)
	{
		x = event->motion.x;
		y = event->motion.y;

		if (infos->over == false && checkCoords(infos, x, y) == true)
		{
			int	tx = translateCoords(infos, x, y, 0);
			int	ty = translateCoords(infos, x, y, 1);

			reactEvent(infos, tx, ty, SDL_MOUSEMOTION);
		}
		else
			infos->xHighLight = -1, infos->xHighLight = -1;

		if (isResetZone(infos, x, y) == true)
			SDL_SetCursor(infos->interactCursor);
		else
			SDL_SetCursor(infos->normalCursor);
	}

	displayGame(infos);
}
