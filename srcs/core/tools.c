#include "header.h"

SDL_Texture*	getTexture(tInfos* infos, const int value, const bool color)
{
	for (int i = 0; i != 9; i++)
	{
		if (value == i)
		{
			if (color == true)
				return (infos->textures.numbersColored[i]);
			else
				return (infos->textures.numbers[i]);
		}
	}

	if (value == 9)
		return (infos->textures.numbers[9]);

	if (value == BOMB1)
		return (infos->textures.bomb1);
	else if (value == BOMB2)
		return (infos->textures.bomb2);

	else if (value == FLAG)
		return (infos->textures.flag);

	else if (value == TIMER)
		return (infos->textures.timer);
	else if (value == SECOND)
		return (infos->textures.second);

	else if (value == ARROW)
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

bool	isResetZone(tInfos* infos, const int x, const int y)
{
	if (y > 9 && y <= 60)
	{
		if (x >= (((infos->width + 1) * 42) - 21 - (45 * (infos->width / 16))) \
			&& x <= ((infos->width + 1) * 42) - 28)
			return (true);
	}

	return (false);
}

int	getBombsNumber(tInfos* infos, const int i, const int k)
{
	int	value = 0;

	if (i > 0 && infos->map[i - 1][k].bomb == true)
		value++;
	if (infos->map[i + 1] != NULL && infos->map[i + 1][k].bomb == true)
		value++;

	if (k > 0 && infos->map[i][k - 1].bomb == true)
		value++;
	if (k + 1 < infos->width && infos->map[i][k + 1].bomb == true)
		value++;

	if (i > 0 && k > 0 && infos->map[i - 1][k - 1].bomb == true)
		value++;
	if (i > 0 && k + 1 < infos->width && infos->map[i - 1][k + 1].bomb == true)
		value++;

	if (infos->map[i + 1] != NULL && k > 0 && infos->map[i + 1][k - 1].bomb == true)
		value++;
	if (infos->map[i + 1] != NULL && k + 1 < infos->width && infos->map[i + 1][k + 1].bomb == true)
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
