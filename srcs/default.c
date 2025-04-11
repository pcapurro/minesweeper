#include "header.h"

void	setTexturesToDefault(tInfos* infos)
{
	infos->textures.zero = NULL;
	infos->textures.one = NULL;
	infos->textures.two = NULL;
	infos->textures.three = NULL;
	infos->textures.four = NULL;

	infos->textures.five = NULL;
	infos->textures.six = NULL;
	infos->textures.seven = NULL;
	infos->textures.eight = NULL;
	infos->textures.nine = NULL;

	infos->textures.bomb1 = NULL;
	infos->textures.bomb2 = NULL;

	infos->textures.flag = NULL;
	infos->textures.timer = NULL;

	infos->textures.arrow = NULL;
}

void	setAllToDefault(tInfos* infos)
{
	infos->width = 16;
	infos->height = 16;

	infos->bombs = 21;
	infos->flags = 21;

	infos->startTime = 0;
	infos->finalTime = 0;

	infos->xHighLight = -1;
	infos->yHighLight = -1;

	infos->moves = 0;
	infos->over = false;

	infos->mainWindow = NULL;
	infos->mainRenderer = NULL;

	infos->normalCursor = NULL;
	infos->interactCursor = NULL;

	infos->map = NULL;
}
