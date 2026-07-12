#include "header.h"

SDL_Texture*	getTexture(tInfos* infos, const int value, const bool color)
{
	for (int i = 0; i != 9; i++)
	{
		if (value == i)
		{
			if (color == true)
				return infos->textures.numbersColored[i];
			else
				return infos->textures.numbers[i];
		}
	}

	if (value == 9)
		return infos->textures.numbers[9];

	if (value == BOMB1)
		return infos->textures.bomb1;
	else if (value == BOMB2)
		return infos->textures.bomb2;

	else if (value == FLAG)
		return infos->textures.flag;

	else if (value == TIMER)
		return infos->textures.timer;
	else if (value == SECOND)
		return infos->textures.second;

	else if (value == ARROW)
		return infos->textures.arrow;

	return NULL;
}

bool	isOver(tInfos* infos)
{
	for (int y = 0; infos->map[y] != NULL; y++)
	{
		for (int x = 0; x != infos->width; x++)
		{
			if (infos->map[y][x].discovered == false && infos->map[y][x].bomb == false)
				return false;
		}
	}

	if (infos->flags != 0)
		return false;

	return true;
}

bool	checkCoords(tInfos* infos, const int x, const int y)
{
	if (x < 21 || x > 21 + (infos->width * 42))
		return false;

	if (y < 70 || y > 70 + (infos->height * 42))
		return false;

	return true;
}

bool	isResetZone(tInfos* infos, const int x, const int y)
{
	if (y > 9 && y <= 60)
	{
		if (x >= (((infos->width + 1) * 42) - 21 - (45 * (infos->width / 16))) \
			&& x <= ((infos->width + 1) * 42) - 28)
			return (true);
	}

	return false;
}

int	getBombsNumber(tInfos* infos, const int y, const int x)
{
	int	value = 0;

	if (y > 0 && infos->map[y - 1][x].bomb == true)
		value++;
	if (infos->map[y + 1] != NULL && infos->map[y + 1][x].bomb == true)
		value++;

	if (x > 0 && infos->map[y][x - 1].bomb == true)
		value++;
	if (x + 1 < infos->width && infos->map[y][x + 1].bomb == true)
		value++;

	if (y > 0 && x > 0 && infos->map[y - 1][x - 1].bomb == true)
		value++;
	if (y > 0 && x + 1 < infos->width && infos->map[y - 1][x + 1].bomb == true)
		value++;

	if (infos->map[y + 1] != NULL && x > 0 && infos->map[y + 1][x - 1].bomb == true)
		value++;
	if (infos->map[y + 1] != NULL && x + 1 < infos->width && infos->map[y + 1][x + 1].bomb == true)
		value++;

	return value;
}

int		translateCoords(tInfos* infos, const int tX, const int tY, const char value)
{
	int		actualX, actualY;
	int		actualW, actualH;

	actualX = 21;
	actualY = 70;

	for (int y = 0; infos->map[y] != NULL; y++)
	{
		for (int x = 0; x != infos->width; x++)
		{
			actualW = (infos->width * 42) / infos->width;
			actualH = (infos->height * 42) / infos->height;

			actualX = 21 + (x * actualW);

			if (tX >= actualX && tX <= actualX + actualW)
			{
				if (tY >= actualY && tY <= actualY + actualH)
				{
					if (value == 'x')
						return x;

					if (value == 'y')
						return y;
				}
			}
		}

		actualY = 70 + ((y + 1) * actualH);
	}

	return 0;
}
