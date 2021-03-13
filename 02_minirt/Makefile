# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/01 05:08:59 by sehpark           #+#    #+#              #
#    Updated: 2021/03/11 22:45:42 by sehpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------- VARIABLES ---------------------------------#

NAME = minirt

# Color codes (Can be changed).
RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m

#-------------------------------- MISCELANEOUS --------------------------------#

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs

INCS	= -I ./includes/

SRC		= ./srcs/

#--------------------------------- COMPILATION --------------------------------#

OBJS	= $(addprefix $(SRC), $(SRCS:.c=.o))
OBJS_B	= $(addprefix $(SRC), $(SRCS_B:.c=.o))

#----------------------------------- FILES ------------------------------------#

LFT		= libft/libft.a
LINK	= -L libft -lft -L minilibx-linux -l mlx -lm -lXext -lX11 -lbsd

SRCS	= minirt.c \
		  io/get_next_line.c \
		  io/read_rt.c \
		  io/mlx.c \
		  io/export_bmp.c \
		  io/print_window.c \
		  io/rt/rt_ambientlight.c \
		  io/rt/rt_camera.c \
		  io/rt/rt_light.c \
		  io/rt/rt_cylinder.c \
		  io/rt/rt_plane.c \
		  io/rt/rt_triangle.c \
		  io/rt/rt_rect.c \
		  io/rt/rt_xyrect.c \
		  io/rt/rt_xzrect.c \
		  io/rt/rt_yzrect.c \
		  io/rt/rt_resolution.c \
		  io/rt/rt_sphere.c \
		  io/rt/rt_square.c \
		  io/tools/atovec3.c \
		  io/tools/check_atof_parameter.c \
		  io/tools/check_atoi_parameter.c \
		  io/tools/check_range.c \
		  io/tools/skip.c \
		  io/tools/get_material_attr.c \
		  vector/operation_random.c \
		  vector/operations.c \
		  vector/operations2.c \
		  vector/operations3.c \
		  vector/operations4.c \
		  viewport/viewport.c \
		  object/object.c \
		  object/cylinder.c \
		  object/sphere.c \
		  object/square.c \
		  object/plane.c \
		  object/triangle.c \
		  object/rect.c \
		  object/xyrect.c \
		  object/xzrect.c \
		  object/yzrect.c \
		  image/image.c \
		  image/image_render.c \
		  tools/error_handle.c \
		  tools/random.c \
		  tools/clamp.c \
		  tools/degrees_to_radians.c \
		  brdf/onb.c \
		  brdf/fresnel.c \
		  brdf/light_pdf.c \
		  brdf/operation.c \
		  brdf/operation2.c \
		  brdf/set_brdf.c \
		  brdf/record.c \
		  brdf/check_box.c \
		  brdf/transparent.c \
		  brdf/lambertian.c \
		  brdf/mirror.c \
		  brdf/microfacet.c \
		  brdf/microfacet_eval.c \
		  brdf/microfacet_function.c \
		  trace/trace.c \
		  trace/ray.c \

SRCS_B	=

#----------------------------------- RULES ------------------------------------#

ifeq ($(OS),Windows_NT)
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
#linux
LINK	+= -L minilibx-linux -lmlx -lm -lXext -lX11 -lbsd
LMLX	= minilibx-linux/libmlx.a
$(LMLX):
	@$(MAKE) -sC minilibx-linux

    endif
    ifeq ($(UNAME_S),Darwin)
#mac
LINK	+= -L minilibx_mmx_20200219 -lmlx -framework OpenGL -framework Appkit
LMLX	= minilibx_mms_20200219/libmlx.a
$(LMLX):
	@$(MAKE) -sC minilibx_mms_20200219

    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
    endif
endif

$(NAME): $(LFT) $(LMLX) $(OBJS)
	$(CC) $(CFLAGS) $(INCS) $(OBJS) $(LINK) -o $(NAME) -fsanitize=address

$(LFT):
	@$(MAKE) -sC libft

.c.o:
	$(CC) $(CFLAGS) $(INCS) -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(NAME)

clean:
	@$(MAKE) -sC libft clean
	@$(MAKE) -sC minilibx-linux clean
	@$(MAKE) -sC minilibx_mms_20200219 clean
	@rm -f $(OBJS) $(OBJS_B)

fclean: 
	@$(MAKE) -sC libft fclean
	@$(MAKE) -sC minilibx-linux clean
	@$(MAKE) -sC minilibx_mms_20200219 clean
	@rm -f $(OBJS) $(OBJS_B)
	@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus .c.o
