# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/01 05:08:59 by sehpark           #+#    #+#              #
#    Updated: 2020/12/10 05:35:10 by sehpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------- VARIABLES ---------------------------------#

NAME = minirt

# Color codes (Can be changed).
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m

#-------------------------------- MISCELANEOUS --------------------------------#

CC		= clang
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
MLXFLAGS= -lm -lXext -lX11 -lbsd

INCS	= -I ./includes/
INCS_MLX= -I ./minilibx-linux/

SRC		= ./srcs/

#--------------------------------- COMPILATION --------------------------------#

OBJS	= $(addprefix $(SRC), $(SRCS:.c=.o))
OBJS_B	= $(addprefix $(SRC), $(SRCS_B:.c=.o))

#----------------------------------- FILES ------------------------------------#

LFT		= libft/libft.a
LMLX	= minilibx-linux/libmlx.a

CONVERT	= convert/
SRCS	= 
SRCS_B	=

#----------------------------------- RULES ------------------------------------#

$(NAME): $(LFT) $(LMLX) $(OBJS)
		$(CC) -o $(NAME) main.c $(CFLAGS) $(MLXFLAGS) $(INCS) $(INCS_MLX) $(LMLX) $(LFT)
	
$(LFT):
	@$(MAKE) -s -C libft

$(LMLX):
	@$(MAKE) -s -C minilibx-linux

.c.o:
	$(CC) $(CFLAGS) $(INCS) $(INCS_MLX) -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(NAME)

clean:
	@$(MAKE) -sC libft clean
	@$(MAKE) -sC minilibx-linux clean
	@rm -f $(OBJS) $(OBJS_B)

fclean: 
	@$(MAKE) -sC libft fclean
	@$(MAKE) -sC minilibx-linux clean
	@rm -f $(OBJS) $(OBJS_B)
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus .c.o
