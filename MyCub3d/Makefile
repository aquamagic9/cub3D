NAME	= cub3D

SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj
LIBFTDIR	= ./libft

SRC		= main.c \
		  draw.c \
		  init.c \
		  key.c \
		  raycasting.c \
		  vector_utils.c \


OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -O3

MLX		= ./mlx/
MLX_LNK	= -L $(MLX) -lmlx -framework OpenGL -framework AppKit


MLX_INC	= -I $(MLX)
MLX_LIB	= $(addprefix $(MLX),mlx.a)

LIBFT_LIB = -L$(LIBFTDIR) -lft

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
	$(MAKE) -C $(LIBFTDIR)
	$(CC) $(OBJ) $(MLX_LNK) $(LIBFT_LIB) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(LIBFTDIR) clean
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re