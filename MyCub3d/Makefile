NAME	= cub3D

SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

SRC		= main.c \
		  draw.c \
		  init.c \
		  key.c \
		  raycasting.c \
		  vector_utils.c \


OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -O3

MLX		= ./mlx/
MLX_LNK	= -L $(MLX) -lmlx -framework OpenGL -framework AppKit


MLX_INC	= -I $(MLX)
MLX_LIB	= $(addprefix $(MLX),mlx.a)

all: obj $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) -I $(INCDIR) -o $@ -c $<

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(MLX) clean

fclean: clean
	rm -rf $(NAME)

re: fclean all