# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 01:41:01 by dwanetta          #+#    #+#              #
#    Updated: 2021/05/14 12:36:56 by kgale            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
FLAGS = #-Wall -Wextra -Werror
LIB = -L mlx_mac  -L libft
OPTION_LIB = -lmlx -framework OpenGL -framework AppKit -lft
OPTION = -c
LIBFT = make -C libft
SRCS =	main.c\
		parser/check_arguments.c\
		parser/errors.c\
		parser/flag_parser_utils.c\
		parser/flag_parser.c\
		parser/map_to_mass_utils.c\
		parser/map_to_mass.c\
		parser/parser.c\
		mlx_drawer/bmp.c\
		mlx_drawer/draw_sprite.c\
		mlx_drawer/draw_walls.c\
		mlx_drawer/exit.c\
		mlx_drawer/mlx_utils.c\
		mlx_drawer/move_player_utils.c\
		mlx_drawer/move_player.c\
		mlx_drawer/raycast.c\
		mlx_drawer/sprite_utils.c\
		mlx_drawer/window_creation.c

OBJS_SRCS = ${SRCS:.c=.o}
OBJS =	$(OBJS_SRCS)

all: $(NAME)

$(NAME) : $(OBJS_SRCS)
		@$(CC) $(FLAGS) $(OPTION) $(SRCS)
		@$(LIBFT)
		@$(CC) $(LIB) $(OPTION_LIB) $(OBJS_SRCS) -o $(NAME)
clean:
		rm -f $(OBJS_SRCS)
		@$(LIBFT) clean
fclean: clean
		rm -f $(NAME)
		rm -f *.bmp
		@$(LIBFT) fclean
re: fclean all
.PHONY: all clean fclean re
