#include "header.h"

void	help(void)
{
	writeStr("Usage: './minesweeper [map width] [map height]'\n", 1);
	writeStr("Supported resolutions: 16x16, 32x32, 64x64.\n", 1);
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
