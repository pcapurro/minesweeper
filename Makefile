# # #==============# # #
# # ### MAKEFILE ### # #
# # #==============# # #

## === VARIABLES === ##

NAME = minesweeper

SRCS = srcs/main.c \
	srcs/default.c \
	srcs/help.c \
	srcs/core/core.c \
	srcs/core/init.c \
	srcs/core/tools.c \
	srcs/core/display.c \
	srcs/core/event.c \
	srcs/core/utils.c \
	srcs/core/end.c \

CC = gcc

CFLAGS =  -Wall -Wextra -Werror -I include/

SDLFLAG = -lSDL2

## == .C TO .O == ##

OBJS = $(SRCS:.c=.o)

## === RULES === ##

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(SDLFLAG)

re: fclean all

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
