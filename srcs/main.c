#include "header.h"

void	setToDefault(tInfos* infos)
{
	infos->width = 640;
	infos->height = 640;

	infos->mainWindow = NULL;
	infos->mainRenderer = NULL;

	infos->normalCursor = NULL;
	infos->interactCursor = NULL;

	infos->map = NULL;
}

int	main(const int argc, const char** argv)
{
	tInfos	infos;

	setToDefault(&infos);

	initializeGame(&infos);

	startGame(&infos);

	endFree(&infos);

	(void) argc;
	(void) argv;

	return (0);
}