#include "header.h"

bool	checkCoords(tInfos* infos, const int x, const int y)
{
	if (x < 21 || x > 21 + (infos->width * 42))
		return (false);

	if (y < 70 || y > 70 + (infos->height * 42))
		return (false);

	return (true);
}

int		translateCoords(tInfos* infos, const int x, const int y, const int value)
{
	int		actualX, actualY;
	int		actualW, actualH;

	actualX = 21;
	actualY = 70;

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			actualW = (infos->width * 42) / infos->width;
			actualH = (infos->height * 42) / infos->height;

			actualX = 21 + (k * actualW);

			if (x >= actualX && x <= actualX + actualW)
			{
				if (y >= actualY && y <= actualY + actualH)
				{
					if (value == 0)
						return (i);
					else
						return (k);
				}
			}
		}
		actualY = 70 + ((i + 1) * actualH);
	}

	return (0);
}

void	discoverZone(tInfos* infos, const int x, const int y)
{
	;
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

void	sortEvent(tInfos* infos, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN \
		&& event->key.keysym.sym == SDLK_RETURN)
		resetGame(infos);

	if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (checkCoords(infos, event->button.x, event->button.y) == true)
		{
			int x = translateCoords(infos, event->button.x, event->button.y, 0);
			int y = translateCoords(infos, event->button.x, event->button.y, 1);

			if (event->button.button == SDL_BUTTON_LEFT)
			{
				infos->map[x][y].discovered = true;
				if (infos->map[x][y].flag == true)
					infos->map[x][y].flag = false, infos->flags++;

				if (infos->map[x][y].bomb == true) {
					discoverMap(infos);
					infos->over = true;
					return ;
				}
				else if (infos->map[x][y].value == 0)
					discoverZone(infos, x, y);
			}
			if (event->button.button == SDL_BUTTON_RIGHT \
				&& infos->map[x][y].discovered == false)
			{
				if (infos->map[x][y].flag == true)
					infos->map[x][y].flag = false, infos->flags++;
				else if (infos->flags > 0)
					infos->map[x][y].flag = true, infos->flags--;
			}
		}
	}

	displayGame(infos);
}
