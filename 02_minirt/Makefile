# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/01 05:08:59 by sehpark           #+#    #+#              #
#    Updated: 2021/01/31 06:33:33 by sehpark          ###   ########.fr        #
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

SRCS	= minirt.c \
		  io/get_next_line.c \
		  io/read_rt.c \
		  io/output.c \
		  io/rt/rt_ambientlight.c \
		  io/rt/rt_camera.c \
		  io/rt/rt_light.c \
		  io/rt/rt_rect.c \
		  io/rt/rt_resolution.c \
		  io/rt/rt_sphere.c \
		  io/rt/tools/atovec3.c \
		  io/rt/tools/check_atof_parameter.c \
		  io/rt/tools/check_atoi_parameter.c \
		  io/rt/tools/next.c \
		  vector/operations.c \
		  viewport/viewport.c \
		  viewport/ray.c \
		  viewport/hit_record.c \
		  object/object.c \
		  object/sphere.c \
		  object/rect.c \
		  object/lambertian_scatter.c \
		  object/metal_scatter.c \
		  object/dielectric_scatter.c \
		  image/image.c \
		  image/image_render.c \
		  tools/error_handle.c \
		  tools/random_double.c \
		  tools/clamp.c \
		  tools/degrees_to_radians.c


SRCS_B	=

#----------------------------------- RULES ------------------------------------#

$(NAME): $(LFT) $(LMLX) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(MLXFLAGS) $(INCS) $(INCS_MLX) $(LMLX) $(LFT) -fsanitize=address
	
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
