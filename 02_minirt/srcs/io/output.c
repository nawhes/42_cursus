/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 05:07:52 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 06:26:21 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "mlx.h"

t_output	*output(char *title, t_minirt *rt)
{
	t_output	*p_output;
	t_list		*p_list;
	t_image		*p_img;

	if (!(p_output = malloc(sizeof(t_output))))
		return (NULL);
	p_list = (t_list *)(rt->p_image);
	p_img = (t_image *)(p_list->content);
	p_output->mlx = mlx_init();
	p_output->win = mlx_new_window(p_output->mlx, p_img->width, p_img->height, title);
	p_output->info = malloc(sizeof(t_info) * ft_lstsize(p_list));
	if (p_output->mlx == NULL || p_output->win == NULL || p_output->info == NULL)
		return (NULL);
	return (p_output);
}

int			output_print(t_output *out, t_minirt *rt)
{
	int		i;
	int		j;
	int		next;
	t_image	*p_img;
	t_info	*info;

	p_img = (t_image *)(rt->p_image->content);
	info = out->info;
	info->img = mlx_new_image(out->mlx, p_img->width, p_img->height);
	info->addr = mlx_get_data_addr(info->img, &info->bit_per_pixel,
			&info->size_line, &info->endian);
	i = 0;
	while (i < p_img->width)
	{
		j = 0;
		while (j < p_img->height)
		{
			next = (p_img->height - j - 1) * info->size_line;
			next += i * (info->bit_per_pixel / 8);
			*(uint32_t *)(info->addr + next) = p_img->rgb[i][j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(out->mlx, out->win, info->img, 0, 0);
	return (0);
}
