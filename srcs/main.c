#include "header.h"

void	setToDefault(tInfos* infos)
{
	infos->width = 16;
	infos->height = 16;

	infos->bombs = 21;
	infos->flags = 21;

	infos->moves = 0;
	infos->over = false;

	infos->mainWindow = NULL;
	infos->mainRenderer = NULL;

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

	infos->normalCursor = NULL;
	infos->interactCursor = NULL;

	infos->map = NULL;
}

bool	validateArguments(const int argc, const char** argv)
{
	if (argc != 3 && argc != 4)
		return (false);

	if (atoi(argv[1]) < 16 || atoi(argv[1]) > 21)
		return (false);

	if (atoi(argv[2]) < 16 || atoi(argv[2]) > 21)
		return (false);

	if (argc == 4)
	{
		if (atoi(argv[3]) <= 0 || atoi(argv[3]) > 60)
			return (false);
	}

	return (true);
}

int	main(const int argc, const char** argv)
{
	tInfos	infos;

	setToDefault(&infos);

	if (argc != 1 && isHelp(argv) == true)
		help(), exit(0);

	if (argc >= 3 && validateArguments(argc, argv) == true)
	{
		if (argc >= 3)
			infos.width = atoi(argv[1]), infos.height = atoi(argv[2]);

		if (argc == 4)
			infos.bombs = atoi(argv[3]);
	}

	initializeMap(&infos);

	initializeDisplay(&infos);

	startGame(&infos);

	endFree(&infos);

	return (0);
}
