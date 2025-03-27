#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <time.h>
# include <error.h>

# include <sys/time.h>

# include <SDL2/SDL.h>

struct sInfos
{
	int				width, height;

	SDL_Window*		mainWindow;
	SDL_Renderer*	mainRenderer;

	SDL_Cursor		*normalCursor;
	SDL_Cursor		*interactCursor;

	char*			map;
};

typedef struct sInfos tInfos;

int			getLen(const char* str);
void		writeStr(const char* str, const int fd);
bool		isSame(const char* str1, const char* str2);

void		endError(tInfos* infos, const int value);
void		endFree(tInfos* infos);

void		displayGame(tInfos* infos);

void		initializeGame(tInfos* infos);
void		startGame(tInfos* infos);

int			getRandomNumber(void);

bool		isHelp(const char** argv);
void		help(void);

int			main(const int argc, const char** argv);

#endif