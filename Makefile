NAME	=	Cub3D

SRC		=

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CFLAGS	=	-Isrcs -Wall -Werror -Wextra -lmlx

OS		=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXDIR	=	mlx_linux/
	CFLAGS	+=	-I$(MLXDIR) -L$(MLXDIR) -lXext -lX11
else
	MLXDIR	=	mlx_opengl/
	CFLAGS	+=	-I$(MLXDIR) -L$(MLXDIR) -framework OpenGL -framework AppKit
endif

OBJS/%.o:	%.c
			mkdir -p objs
			$(CC) -c $(CFLAGS) $< -o $@d

all:		$(NAME)

os:
			@echo "$(OS)"

cflags:	
			@echo "$(CFLAGS)"

$(NAME):	$(addprefix srcs/, $(OBJS))
			make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -o $(NAME)

test:
			make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -o mlx_test mlx_test.c
