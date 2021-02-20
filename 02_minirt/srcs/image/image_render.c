/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:48:59 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/21 05:08:57 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"

int				get_color(t_vec3 color, int sample_per_pixel)
{
	int			ret;
	double		scale;
	
	if (color.x != color.x)
		color.x = 0.0;
	if (color.y != color.y)
		color.y = 0.0;
	if (color.z != color.z)
		color.z = 0.0;

	scale = 1.0 / (double)sample_per_pixel;
	color.x = sqrt(color.x * scale);
	color.y = sqrt(color.y * scale);
	color.z = sqrt(color.z * scale);

	ret = (int)(256.0 * clamp(color.x, 0.0, 0.999));
	ret <<= 8;
	ret += (int)(256.0 * clamp(color.y, 0.0, 0.999));
	ret <<= 8;
	ret += (int)(256.0 * clamp(color.z, 0.0, 0.999));
	return (ret);
}

void			image_render(t_minirt *rt)
{
	int			i;
	int			j;
	int			k;
	double		u;
	double		v;
	t_ray		ray;
	t_vec3		rgb;
	t_image		*image;
	t_viewport	*viewport;

	image = rt->p_image->content;
	viewport = rt->p_viewport->content;

	j = image->height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < image->width)
		{
			k = 0;
			rgb = vec3(0, 0, 0);
			while (k < SAMPLE_PER_PIXEL)
			{
				u = ((double)i + random_double()) / (image->width - 1);
				v = ((double)j + random_double()) / (image->height - 1);
			//	u = ((double)i) / (image->width - 1);
			//	v = ((double)j) / (image->height - 1);
				ray = viewport->get_ray(*viewport, u, v);
				rgb = vec3_add(rgb, ray_color(ray, rt, MAX_DEPTH));
				k++;
			}
			image->rgb[i][j] = get_color(rgb, SAMPLE_PER_PIXEL);
			i++;
		}
		j--;
	}
}
