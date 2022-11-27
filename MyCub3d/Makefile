# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/27 23:04:28 by junseo            #+#    #+#              #
#    Updated: 2022/11/27 23:04:42 by junseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj
LIBFTGNL_DIR	= ./libft

SRC		= main.c \
		  draw.c \
		  init.c \
		  key.c \
		  raycasting.c \
		  vector_utils.c \
	      parse.c \
		  error.c \
		  utils.c \
		  validation.c \
		  map.c \
		  config_setter.c\
		  load.c

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -O3

MLX		= ./mlx/
MLX_LNK	= -L $(MLX) -lmlx -framework OpenGL -framework AppKit


MLX_INC	= -I $(MLX)
MLX_LIB	= $(addprefix $(MLX),mlx.a)

LIBFT_LIB = -L$(LIBFTGNL_DIR) -lftgnl

all: obj $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) -I $(INCDIR) -o $@ -c $<

$(MLX_LIB):
	@make -C $(MLX)

$(LIBFT):
	@make -C $(LIBFTDIR)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTGNL_DIR)
	$(CC) $(OBJ) $(MLX_LNK) $(LIBFT_LIB) $(CFLAGS) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTGNL_DIR) clean
	$(MAKE) -C $(MLX) clean

fclean: clean
	$(MAKE) -C $(LIBFTGNL_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re