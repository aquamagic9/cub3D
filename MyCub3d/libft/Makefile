# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/22 21:48:39 by junseo            #+#    #+#              #
#    Updated: 2022/06/24 09:41:31 by junseo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT 		=	src/libft/libft.a

NAME	= libftgnl.a

LIBFT_DIR	=	src/libft
GNL_DIR		=	src/get_next_line

SRCS	= 	$(GNL_DIR)/get_next_line.c

OBJS	= $(SRCS:.c=.o)

CC		= cc
AR		= ar crs
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

all:		$(NAME)

.c.o:		$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			cp $(LIBFT) ./$(NAME)
			$(AR) $(NAME) $(OBJS)

clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		$(RM) $(OBJS)

fclean: clean
		$(MAKE) fclean -C $(LIBFT_DIR)
		$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all, bonus, clean, fclean, re