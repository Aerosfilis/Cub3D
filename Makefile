NAME	=	Cub3D

SRC		=

OBJ		=	$(SRC:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -Isrcs -fsanitize=address

OS		=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXDIR	=	mlx_linux/
	CFLAGS	+=	-I$(MLXDIR)
	GFLAGS	=	-L$(MLXDIR) -lmlx -I$(MLXDIR) -lXext -lX11
else
	MLXDIR	=	mlx_opengl/
	CFLAGS	+=	-I$(MLXDIR)
	GFLAGS	=	-L$(MLXDIR) -lmlx -I$(MLXDIR) -framework OpenGL -framework AppKit
endif

OBJS/%.o:	%.c
			mkdir -p objs
			$(CC) -c $(CFLAGS) $< -o $@d

all:		$(NAME)

$(NAME):	$(addprefix srcs/, $(OBJS))
			make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -o $(NAME) $(GFLAGS)
clean:
			rm -rf objs

fclean:		clean
			rm $(NAME)

re:			fclean all

os:
			@echo "$(OS)"

cflags:	
			@echo "$(CFLAGS)"

test:
			make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -o mlx_test mlx_test.c $(GFLAGS)
