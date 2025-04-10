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
		if (infos->moves == 0 && infos->map[x][y].bomb == false \
			&& infos->map[x][y].value != 0)
			infos->map[x][y].value = 0;

		infos->map[x][y].discovered = true;
		infos->moves++;

		if (infos->map[x][y].flag == true)
			infos->map[x][y].flag = false, infos->flags++;

		if (infos->over == true || infos->map[x][y].bomb == true)
		{
			discoverMap(infos);
			infos->over = true;

			return ;
		}
		else
			discoverZone(infos, x, y);
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
		if (checkCoords(infos, event->button.x, event->button.y) == true)
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

	displayGame(infos);
}
