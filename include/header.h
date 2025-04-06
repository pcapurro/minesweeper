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

struct sCell
{
	bool	flag;
	bool	discovered;

	int		value;
	bool	bomb;
};

typedef struct sCell tCell;

struct sInfos
{
	int				width, height;

	SDL_Window*		mainWindow;
	SDL_Renderer*	mainRenderer;

	SDL_Cursor		*normalCursor;
	SDL_Cursor		*interactCursor;

	tCell**			map;

	int				bombs;
	int				flags;

	int				theme;
};

typedef struct sInfos tInfos;

int			getLen(const char* str);
void		writeStr(const char* str, const int fd);
bool		isSame(const char* str1, const char* str2);
int			getRandomNumber(void);

void		endError(tInfos* infos, const int value);
void		endFree(tInfos* infos);

void		displayGame(tInfos* infos);
void		sortEvent(tInfos* infos, SDL_Event* event);
void		startGame(tInfos* infos);

int			getBombsNumber(tInfos* infos, const int i, const int k);
void		generateMap(tInfos* infos);

void		initializeDisplay(tInfos* infos);
void		initializeMap(tInfos* infos);

bool		isHelp(const char** argv);
void		help(void);

bool		validateArguments(const int argc, const char** argv);

int			main(const int argc, const char** argv);

#endif