# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 17:15:05 by cbugnon           #+#    #+#              #
#    Updated: 2021/03/08 10:53:54 by cbugnon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRC		=	cub3d.c \
			event0.c \
			event1.c \
			parse0.c \
			parse1.c \
			parse2.c \
			render0.c \
			render1.c \
			render2.c \
			render3.c \
			struct0.c \
			struct1.c \
			struct2.c \
			utils0.c \
			utils1.c

B_SRC	=	cub3d_bonus.c \
			event0_bonus.c \
			event1_bonus.c \
			parse0.c \
			parse1.c \
			parse2.c \
			render0_bonus.c \
			render1_bonus.c \
			render2_bonus.c \
			render3_bonus.c \
			struct0.c \
			struct1.c \
			struct2.c \
			utils0.c \
			utils1.c

OBJ		=	$(addprefix objs/, $(SRC:.c=.o))

B_OBJ	=	$(addprefix objs/, $(B_SRC:.c=.o))

DEP		=	$(OBJ:%.o=%.d)

B_DEP	=	$(B_OBJ:%.o=%.d)


################################# BASE FLAGS ###################################

ifeq (, $(shell which clang-9 ))
	CC	:=	clang
else
	CC	:=	clang-9
endif

OPTI	=	O2
CFLAGS	:=	-Wall -Werror -Wextra -flto -Isrcs -$(OPTI)


################################# MAIN OPTIONS #################################

all:		$(NAME)

objs/%.o:	srcs/%.c
			@mkdir -p objs
			$(CC) $(CFLAGS) -MMD -Imlx_linux -c $< -o $@

$(NAME):	$(OBJ)
			@make -C ./mlx_linux --no-print-directory
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -Lmlx_linux -lmlx -lX11 -lXext -lm -lbsd

bonus:		$(B_OBJ)
			@make -C ./mlx_linux --no-print-directory
			$(CC) $(CFLAGS) -o $(NAME) $(B_OBJ) -Lmlx_linux -lmlx -lX11 -lXext -lm -lbsd

clean:
			rm -rf objs

fclean:		clean
			@make -C ./mlx_linux --no-print-directory clean
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
-include $(B_DEP)
