#include "header.h"

void	setTexturesToDefault(tInfos* infos)
{
	for (int i = 0; i != 9; i++)
	{
		infos->textures.numbersColored[i] = NULL;
		infos->textures.numbers[i] = NULL;
	}
	infos->textures.numbers[9] = NULL;

	infos->textures.bomb1 = NULL;
	infos->textures.bomb2 = NULL;

	infos->textures.flag = NULL;

	infos->textures.timer = NULL;
	infos->textures.second = NULL;

	infos->textures.arrow = NULL;
}

void	setAllToDefault(tInfos* infos)
{
	infos->width = 16;
	infos->height = 16;

	infos->bombs = 16;
	infos->flags = 16;

	infos->startTime = 0;
	infos->finalTime = 0;

	infos->xHighLight = -1;
	infos->yHighLight = -1;

	infos->moves = 0;
	infos->over = false;

	infos->mainWindow = NULL;
	infos->mainRenderer = NULL;

	infos->path = NULL;
	setTexturesToDefault(infos);

	infos->normalCursor = NULL;
	infos->interactCursor = NULL;

	infos->map = NULL;
}
