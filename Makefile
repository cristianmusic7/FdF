# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfranco <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/21 15:28:39 by cfranco           #+#    #+#              #
#    Updated: 2018/04/11 15:22:43 by cfranco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

INC = -I minilibx_macos \
	  -I libft

LIBS = -L minilibx_macos \
	  -L libft -lft -lmlx

FRAMEWORKS = -framework OpenGL \
			 -framework AppKit

FLAGS = -Wall -Werror -Wextra

SRC = fdf.c \
		draw.c \
		operations.c \
		transforms.c \
		utils.c

OBJS = ft_*.o

ifdef DEBUG
	FLAGS += -g -fsanitize=address
endif

all: $(NAME)

$(NAME):
	make re -C libft/
	gcc $(FLAGS) $(INC) $(LIBS) $(FRAMEWORKS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME);

re: fclean all
