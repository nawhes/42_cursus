/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 05:07:52 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 06:43:34 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "mlx.h"

int			output_init
(t_output *output, char *title, t_image *image, int count_img)
{
	output->mlx = mlx_init();
	output->win = mlx_new_window(output->mlx,image->width, image->height, title);
	output->info = malloc(sizeof(t_info) * count_img);
	if (output->mlx == NULL || output->win == NULL || output->info == NULL)
		return (1);
	return (0);
}

int			output_print(t_output *output, t_info *info, t_image *image)
{
	int		i;
	int		j;
	int		next;

	info->img = mlx_new_image(output->mlx, image->width, image->height);
	info->addr = mlx_get_data_addr(info->img, &info->bit_per_pixel,
			&info->size_line, &info->endian);
	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			next = (image->height - j - 1) * info->size_line;
			next += i * (info->bit_per_pixel / 8);
			*(uint32_t *)(info->addr + next) = image->rgb[i][j];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(output->mlx, output->win, info->img, 0, 0);
	return (0);
}
