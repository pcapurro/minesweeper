#include "header.h"

void	help(void)
{
	writeStr("Usage: './minesweeper [map width] [map height]'\n", 1);
	writeStr("Map values must be set from 16 to 32.\n", 1);
}

bool	isHelp(const char** argv)
{
	for (int i = 0; argv[i] != NULL; i++)
	{
		if (isSame(argv[i], "-h") == true)
			return (true);

		if (isSame(argv[i], "--help") == true)
			return (true);
	}

	return (false);
}
