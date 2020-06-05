NAME	=	Cub3D

SRC		=	cub3d.c \
			event0.c \
			parse0.c \
			parse1.c \
			parse2.c \
			struct0.c \
			struct1.c \
			utils0.c \
			utils1.c

OBJ		=	$(addprefix objs/, $(SRC:.c=.o))

DEP		=	$(OBJ:%.o=%.d)

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -Isrcs -fsanitize=address

############################ OS SPECIFIC FLAGS #################################

OS		=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXDIR	=	mlx_linux/
	GFLAGS	=	-L$(MLXDIR) -lmlx -I$(MLXDIR) -lXext -lX11
else
	MLXDIR	=	mlx_opengl/
	GFLAGS	=	-L$(MLXDIR) -lmlx -I$(MLXDIR) -framework OpenGL -framework AppKit
endif

############################## MAIN OPTIONS ####################################

all:		$(NAME)

-include $(DEP)
objs/%.o:	srcs/%.c
			@mkdir -p objs
			$(CC) $(CFLAGS) -MMD -Isrcs -c $< -o $@ $(GFLAGS)

$(NAME):	$(OBJ)
			@make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GFLAGS)
clean:
			rm -rf objs

fclean:		clean
			rm -f $(NAME)

re:			fclean all

############################ EXTRA OPTIONS #####################################

os:
			@echo "$(OS)"

cflags:	
			@echo "$(CFLAGS)"

test:
			make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -o mlx_test mlx_test.c $(GFLAGS)

.PHONY:		all clean fclean re $(NAME)
