#include "header.h"

void	discoverZone(tInfos* infos, const int x, const int y)
{
	int value = 0;

	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			if (infos->map[i][k].discovered == true && infos->map[i][k].value == 0)
			{
				if (i != 0 && infos->map[i - 1][k].discovered == false && infos->map[i - 1][k].bomb == false)
				{
					infos->map[i - 1][k].discovered = true;
					if (infos->map[i - 1][k].value == 0)
						value++;
				}

				if (infos->map[i + 1] != NULL && infos->map[i + 1][k].discovered == false \
					&& infos->map[i + 1][k].bomb == false)
				{
					infos->map[i + 1][k].discovered = true;
					if (infos->map[i + 1][k].value == 0)
						value++;
				}

				if (k != 0 && infos->map[i][k - 1].discovered == false \
					&& infos->map[i][k - 1].bomb == false)
				{
					infos->map[i][k - 1].discovered = true;
					if (infos->map[i][k - 1].value == 0)
						value++;
				}

				if (k + 1 != infos->width && infos->map[i][k + 1].discovered == false \
					&& infos->map[i][k + 1].bomb == false)
				{
					infos->map[i][k + 1].discovered = true;
					if (infos->map[i][k + 1].value == 0)
						value++;
				}

				if (i != 0 && k != 0 && infos->map[i - 1][k - 1].discovered == false \
					&& infos->map[i - 1][k - 1].bomb == false)
				{
					infos->map[i - 1][k - 1].discovered = true;
					if (infos->map[i - 1][k - 1].value == 0)
						value++;
				}

				if (i != 0 && k + 1 != infos->width && infos->map[i - 1][k + 1].discovered == false \
					&& infos->map[i - 1][k + 1].bomb == false)
				{
					infos->map[i - 1][k + 1].discovered = true;
					if (infos->map[i - 1][k + 1].value == 0)
						value++;
				}

				if (infos->map[i + 1] != NULL && k != 0 && infos->map[i + 1][k - 1].discovered == false \
					&& infos->map[i + 1][k - 1].bomb == false)
				{
					infos->map[i + 1][k - 1].discovered = true;
					if (infos->map[i + 1][k - 1].value == 0)
						value++;
				}
	
				if (infos->map[i + 1] != NULL && k + 1 != infos->width \
					&& infos->map[i + 1][k + 1].discovered == false && infos->map[i + 1][k + 1].bomb == false)
				{
					infos->map[i + 1][k + 1].discovered = true;
					if (infos->map[i + 1][k + 1].value == 0)
						value++;
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

void	reactEvent(tInfos* infos, const int x, const int y, const int value)
{
	if (value == 0)
	{
		int	value = infos->map[x][y].value;

		if (infos->moves == 0)
		{
			if (infos->map[x][y].bomb == true)
			{
				infos->map[x][y].bomb = false;
				infos->map[x][y].bombType = BOMB1;
			
				int value1 = getRandomNumber() % infos->height;
				int	value2 = getRandomNumber() % infos->width;

				while (infos->map[value1][value2].bomb == true)
				{
					value1 = getRandomNumber() % infos->height;
					value2 = getRandomNumber() % infos->width;
				}

				infos->map[value1][value2].bomb = true;

				int nb = getRandomNumber() % 3;
				if (nb == 0 || nb == 1)
					infos->map[value1][value2].bombType = BOMB1;
				else
					infos->map[value1][value2].bombType = BOMB2;
			}
			else
				infos->map[x][y].value = 0;
		}

		infos->map[x][y].discovered = true;
		infos->moves++;

		if (infos->map[x][y].flag == true)
			infos->map[x][y].flag = false, infos->flags++;

		if (infos->over == true || infos->map[x][y].bomb == true)
		{
			discoverMap(infos);

			infos->over = true;
			infos->finalTime = getTime();

			printf(RED);
			printf("You lost the game.\n");
			printf(COLOR_E);

			printf("Time: %lds.\n\n", (infos->finalTime - infos->startTime) / 1000);

			return ;
		}
		else
			discoverZone(infos, x, y);

		infos->map[x][y].value = value;
	}

	if (value == 1)
	{
		if (infos->map[x][y].flag == true)
			infos->map[x][y].flag = false, infos->flags++;
		else if (infos->flags > 0)
			infos->map[x][y].flag = true, infos->flags--;
	}
}

void	sortEvent(tInfos* infos, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN \
		&& event->key.keysym.sym == SDLK_RETURN)
		resetGame(infos);

	if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (infos->over == false \
			&& checkCoords(infos, event->button.x, event->button.y) == true)
		{
			int x = translateCoords(infos, event->button.x, event->button.y, 0);
			int y = translateCoords(infos, event->button.x, event->button.y, 1);

			if (event->button.button == SDL_BUTTON_LEFT)
				reactEvent(infos, x, y, 0);

			if (event->button.button == SDL_BUTTON_RIGHT \
				&& infos->map[x][y].discovered == false)
				reactEvent(infos, x, y, 1);
		}
	}

	if (event->button.x <= ((infos->width + 1) * 42) - 21 \
		&& event->button.x >= ((infos->width + 1) * 42) - 21 - (45 * (infos->width / 16)))
	{
		if (event->button.y >= 15 && event->button.y <= (45 * (infos->height / 16)))
		{
			SDL_SetCursor(infos->interactCursor);
			if (event->type == SDL_MOUSEBUTTONUP)
				resetGame(infos);
		}
		else
			SDL_SetCursor(infos->normalCursor);
	}

	displayGame(infos);
}
