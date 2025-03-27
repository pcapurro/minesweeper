#include "header.h"

void	setToDefault(tInfos* infos)
{
	infos->mainWindow = NULL;
	infos->mainRenderer = NULL;

	infos->normalCursor = NULL;
	infos->interactCursor = NULL;

	infos->map = NULL;
}

bool	validateArguments(const int argc, const char** argv)
{
	if (argc != 3)
		return (false);

	if (atoi(argv[1]) < 16 || atoi(argv[1]) > 26)
		return (false);

	if (atoi(argv[2]) < 16 || atoi(argv[2]) > 26)
		return (false);

	return (true);
}

int	main(const int argc, const char** argv)
{
	tInfos	infos;

	setToDefault(&infos);

	if (argc != 1 && isHelp(argv) == true)
		help(), exit(0);

	if (argc == 3 && validateArguments(argc, argv) == true)
		infos.width = atoi(argv[1]), infos.height = atoi(argv[2]);
	else
		infos.width = 21, infos.height = 21;

	infos.width = (infos.width + 1) * 30;
	infos.height = (infos.height + 2) * 30;

	initializeGame(&infos);

	startGame(&infos);

	endFree(&infos);

	return (0);
}
