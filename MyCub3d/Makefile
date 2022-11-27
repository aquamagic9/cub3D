# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/27 23:04:28 by junseo            #+#    #+#              #
#    Updated: 2022/11/28 00:18:40 by junseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					= cub3D

SRC_BASE_DIR			= 	./src
BONUS_SRC_BASE_DIR		= 	./src/bonus
INC_BASE_DIR			= 	./includes
BONUS_INC_BASE_DIR		= 	./includes/bonus
OBJ_BASE_DIR			= 	./obj
BONUS_OBJ_BASE_DIR		= 	./obj_bonus

SRC						=	main.c \
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

BONUS_SRC 				=	main_bonus.c \
							draw_bonus.c \
							init_bonus.c \
							key_bonus.c \
							raycasting_bonus.c \
							vector_utils_bonus.c \
							parse_bonus.c \
							error_bonus.c \
							utils_bonus.c \
							validation_bonus.c \
							map_bonus.c \
							config_setter_bonus.c\
							load_bonus.c

OBJ						=	$(addprefix $(OBJ_BASE_DIR)/,$(SRC:.c=.o))
BONUS_OBJ				=	$(addprefix $(BONUS_OBJ_BASE_DIR)/,$(BONUS_SRC:.c=.o))

CC						=	cc
CFLAGS					=	-Wall -Wextra -Werror -g -O3

MLX_DIR					= 	./mlx/
MLX_LNK					=	-L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
MLX_INC					=	-I$(MLX_DIR)
MLX_LIB					=	$(addprefix $(MLX_DIR),mlx.a)

LIBFTGNL_DIR			=	./libft/
LIBFTGNL_LNK			=	-L$(LIBFTGNL_DIR) -lftgnl
LIBFTGNL_INC			=	-I$(LIBFTGNL_DIR)
LIBFTGNL_LIB			=	$(addprefix $(LIBFTGNL_DIR),libftgnl.a)

ifdef BONUS
	OBJECTS				=	$(BONUS_OBJ)
	INC_DIR 			=	$(BONUS_INC_BASE_DIR)
	OBJ_DIR 			=	$(BONUS_OBJ_BASE_DIR)
	SRC_DIR 			=	$(BONUS_SRC_BASE_DIR)
else
	OBJECTS 			=	$(OBJ)
	INC_DIR 			=	$(INC_BASE_DIR)
	OBJ_DIR 			=	$(OBJ_BASE_DIR)
	SRC_DIR 			=	$(SRC_BASE_DIR)
endif

all: obj $(MLX_LIB) $(LIBFTGNL_LIB) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) -I $(INC_DIR) -o $@ -c $<

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIBFTGNL_LIB):
	@make -C $(LIBFTGNL_DIR)

$(NAME): $(OBJECTS)
	$(MAKE) -C $(LIBFTGNL_DIR)
	$(CC) $(OBJECTS) $(MLX_LNK) $(LIBFTGNL_LNK) $(CFLAGS) -lm -o $(NAME)

bonus: 
	$(MAKE) BONUS=1

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BONUS_OBJ_BASE_DIR)
	$(MAKE) -C $(LIBFTGNL_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFTGNL_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus obj