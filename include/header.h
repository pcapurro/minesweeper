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
	int		bombType;
};

typedef struct sCell tCell;

struct sTextures
{
	SDL_Texture*	one;
	SDL_Texture*	two;
	SDL_Texture*	three;
	SDL_Texture*	four;

	SDL_Texture*	five;
	SDL_Texture*	six;
	SDL_Texture*	seven;
	SDL_Texture*	eight;

	SDL_Texture*	bomb1;
	SDL_Texture*	bomb2;

	SDL_Texture*	flag;
	SDL_Texture*	clock;
	
	SDL_Texture*	arrow;
};

typedef struct sTextures tTextures;

struct sInfos
{
	int				width, height;

	SDL_Window*		mainWindow;
	SDL_Renderer*	mainRenderer;

	tTextures		textures;

	SDL_Cursor		*normalCursor;
	SDL_Cursor		*interactCursor;

	tCell**			map;

	int				bombs;
	int				flags;

	int				over;
	int				moves;
};

typedef struct sInfos tInfos;

int				getLen(const char* str);
void			writeStr(const char* str, const int fd);
bool			isSame(const char* str1, const char* str2);
int				getRandomNumber(void);

void			endError(tInfos* infos, const int value);
void			endFree(tInfos* infos);

void			displayGame(tInfos* infos);
void			reactEvent(tInfos* infos, const int x, const int y, const int value);
void			sortEvent(tInfos* infos, SDL_Event* event);
void			startGame(tInfos* infos);
void			resetGame(tInfos* infos);

bool			isOver(tInfos* infos);
bool			checkCoords(tInfos* infos, const int x, const int y);
int				translateCoords(tInfos* infos, const int x, const int y, const int value);
int				getBombsNumber(tInfos* infos, const int i, const int k);
void			generateMap(tInfos* infos);

SDL_Texture*	getTexture(tInfos* infos, const int value);
SDL_Texture*	loadTexture(tInfos* infos, const char* path);

void			initializeTextures(tInfos* infos);

void			initializeDisplay(tInfos* infos);
void			initializeMap(tInfos* infos);

bool			isHelp(const char** argv);
void			help(void);

bool			validateArguments(const int argc, const char** argv);

int				main(const int argc, const char** argv);

#endif