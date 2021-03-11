/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 05:07:52 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 10:44:30 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "mlx.h"
#include <stdio.h>

union		rgba
{
	char	rgb[3];
	char	rgba[4];
	int		color;
};

t_mlx			*mlx(t_minirt *rt)
{
	t_mlx		*p_mlx;
	int			x_screen_size;
	int			y_screen_size;

	if (!(p_mlx = malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(p_mlx->mlx = mlx_init()))
		return (NULL);
	mlx_get_screen_size(p_mlx->mlx, &x_screen_size, &y_screen_size);
	rt->r_x = rt->r_x < x_screen_size ? rt->r_x : x_screen_size;
	rt->r_y = rt->r_y < y_screen_size ? rt->r_y : y_screen_size;
	rt->pixel = rt->r_x * rt->r_y;
	return (p_mlx);
}

int			draw_mlx(t_mlx *mlx, t_minirt *rt, t_image *p_img)
{
	int		i;
	int		j;
	int		next;
	union rgba	rgba;

	i = 0;
	while (i < rt->r_y)
	{
		j = 0;
		while (j < rt->r_x)
		{
			next = i * mlx->size_line;
			next += j * (mlx->bit_per_pixel / 8);
			rgba.color = p_img->rgba[i * rt->r_x + j];
			if (mlx->bit_per_pixel == 32)
				ft_memcpy(mlx->addr + next, rgba.rgba, 4);
			if (mlx->bit_per_pixel == 24)
				ft_memcpy(mlx->addr + next, rgba.rgb, 3);
			j++;
		}
		i++;
	}
	return (0);
}
