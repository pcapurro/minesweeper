#include "header.h"

SDL_Texture*	getTexture(tInfos* infos, const int value)
{
	if (value == 0)
		return (infos->textures.zero);
	if (value == 1)
		return (infos->textures.one);
	if (value == 2)
		return (infos->textures.two);
	if (value == 3)
		return (infos->textures.three);
	if (value == 4)
		return (infos->textures.four);

	if (value == 5)
		return (infos->textures.five);
	if (value == 6)
		return (infos->textures.six);
	if (value == 7)
		return (infos->textures.seven);
	if (value == 8)
		return (infos->textures.eight);
	if (value == 9)
		return (infos->textures.nine);

	if (value == BOMB1)
		return (infos->textures.bomb1);
	if (value == BOMB2)
		return (infos->textures.bomb2);

	if (value == FLAG)
		return (infos->textures.flag);
	if (value == TIMER)
		return (infos->textures.timer);

	if (value == ARROW)
		return (infos->textures.arrow);

	return (NULL);
}

bool	isOver(tInfos* infos)
{
	for (int i = 0; infos->map[i] != NULL; i++)
	{
		for (int k = 0; k != infos->width; k++)
		{
			if (infos->map[i][k].discovered == false && infos->map[i][k].bomb == false)
				return (false);
		}
	}

	if (infos->flags != 0)
		return (false);

	return (true);
}

bool	checkCoords(tInfos* infos, const int x, const int y)
{
	if (x < 21 || x > 21 + (infos->width * 42))
		return (false);

	if (y < 70 || y > 70 + (infos->height * 42))
		return (false);

	return (true);
}

int	getBombsNumber(tInfos* infos, const int i, const int k)
{
	int	value = 0;

	if (infos->map[i][k].bomb == true)
		value++;

	if (i != 0 && infos->map[i - 1][k].bomb == true)
		value++;
	if (infos->map[i + 1] != NULL && infos->map[i + 1][k].bomb == true)
		value++;

	if (k != 0 && infos->map[i][k - 1].bomb == true)
		value++;
	if (k + 1 != infos->width && infos->map[i][k + 1].bomb == true)
		value++;

	if (i != 0 && k != 0 && infos->map[i - 1][k - 1].bomb == true)
		value++;
	if (i != 0 && k + 1 != infos->width && infos->map[i - 1][k + 1].bomb == true)
		value++;

	if (infos->map[i + 1] != NULL && k != 0 && infos->map[i + 1][k - 1].bomb == true)
		value++;
	if (infos->map[i + 1] != NULL && k + 1 != infos->width && infos->map[i + 1][k + 1].bomb == true)
		value++;

	return (value);
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
