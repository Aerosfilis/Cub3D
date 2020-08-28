# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 17:15:05 by cbugnon           #+#    #+#              #
#    Updated: 2020/08/28 05:32:48 by cbugnon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRC		=	cub3d.c \
			event0.c \
			parse0.c \
			parse1.c \
			parse2.c \
			render0.c \
			struct0.c \
			struct1.c \
			struct2.c \
			utils0.c \
			utils1.c

OBJ		=	$(addprefix objs/, $(SRC:.c=.o))

DEP		=	$(OBJ:%.o=%.d)

CC		=	gcc
OPTI	=	O2
CFLAGS	=	-Wall -Werror -Wextra -flto -Isrcs -$(OPTI)


################################### OS FLAGS ###################################

OS		=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXDIR	=	mlx_linux/
	GFLAGS	=	-L$(MLXDIR) -lmlx -I$(MLXDIR) -lXext -lX11 -lm
else
	MLXDIR	=	mlx_opengl/
	GFLAGS	=	-L$(MLXDIR) -lmlx -I$(MLXDIR) -framework OpenGL -framework AppKit -lm
endif


################################# EXTRA  FLAGS #################################

DEBUGLOOP 	=	0
ifneq ($(DEBUGLOOP), 0)
	CFLAGS += -DDEBUGLOOP=$(DEBUGLOOP) -g
endif


################################# MAIN OPTIONS #################################

all:		$(NAME)

objs/%.o:	srcs/%.c
			@mkdir -p objs
			$(CC) $(CFLAGS) -MMD -Isrcs -c $< -o $@ $(GFLAGS)

$(NAME):	$(OBJ)
			@make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -c srcs/render0.c -o objs/render0.o $(GFLAGS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GFLAGS)

bonus:		$(OBJ)
			@make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -DSHADOW=1 -c srcs/render0.c -o objs/render0.o $(GFLAGS)
			$(CC) $(CFLAGS) -fuse-linker-plugin -o $(NAME) $(OBJ) $(GFLAGS)

clean:
			rm -rf objs

fclean:		clean
			rm -f $(NAME)

re:			fclean all


################################# EXTRA OPTIONS ################################

os:
			@echo "$(OS)"

cflags:	
			@echo "$(CFLAGS)"

test:
			@make -C ./$(MLXDIR) --no-print-directory
			$(CC) $(CFLAGS) -o mlx_test mlx_test.c $(GFLAGS)

.PHONY:		all clean fclean re $(NAME)
-include $(DEP)
