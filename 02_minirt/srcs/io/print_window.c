/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:39:46 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 14:04:37 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int			exit_program(t_minirt *rt)
{
	mlx_destroy_image(rt->p_mlx->mlx, rt->p_mlx->img);
	mlx_destroy_window(rt->p_mlx->mlx, rt->p_mlx->win);
	before_exit(rt);
	exit(0);
	return (0);
}

static int	key_in(int keycode, t_minirt *rt)
{
	if (keycode == KEY_SPACE && ft_lstsize(rt->p_image) != 1)
	{
		printf("SWITCH CAMERA\n");
		if (rt->p_image_iter->next)
			rt->p_image_iter = rt->p_image_iter->next;
		else
			rt->p_image_iter = rt->p_image;
		draw_mlx(rt->p_mlx, rt, rt->p_image_iter->content);
		mlx_put_image_to_window(rt->p_mlx->mlx, rt->p_mlx->win,
			rt->p_mlx->img, 0, 0);
	}
	if (keycode == KEY_ESCAPE)
	{
		printf("ESCAPE\n");
		exit_program(rt);
	}
	return (0);
}

void		print_window(char *title, t_minirt *rt)
{
	t_image		*p_image;

	rt->p_mlx->win = mlx_new_window(rt->p_mlx->mlx, rt->r_x, rt->r_y, title);
	rt->p_mlx->img = mlx_new_image(rt->p_mlx->mlx, rt->r_x, rt->r_y);
	if (rt->p_mlx->win == NULL || rt->p_mlx->img == NULL)
		error_handle(-4, rt);
	rt->p_mlx->addr = mlx_get_data_addr(rt->p_mlx->img,
			&rt->p_mlx->bit_per_pixel, &rt->p_mlx->size_line,
			&rt->p_mlx->endian);
	if (rt->p_mlx->bit_per_pixel != 24 && rt->p_mlx->bit_per_pixel != 32)
		error_handle(-4, rt);
	rt->p_image_iter = rt->p_image;
	p_image = rt->p_image_iter->content;
	draw_mlx(rt->p_mlx, rt, p_image);
	mlx_put_image_to_window(rt->p_mlx->mlx, rt->p_mlx->win,
			rt->p_mlx->img, 0, 0);
	mlx_hook(rt->p_mlx->win, 2, 1L << 0, key_in, rt);
	mlx_hook(rt->p_mlx->win, 17, 1L << 17, exit_program, rt);
	mlx_loop(rt->p_mlx->mlx);
}
