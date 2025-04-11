#include "header.h"

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

	setAllToDefault(&infos);

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

	endFree(&infos, 0);

	return (0);
}
