/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:48:59 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/04 02:00:14 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "image.h"
#include "viewport.h"
#include "tools.h"

int				get_color(t_vec3 color, int sample_per_pixel)
{
	int			ret;
	double		scale = 1.0 / sample_per_pixel;
	int			r;
	int			g;
	int			b;
	
	color.x = sqrt(color.x * scale);
	color.y = sqrt(color.y * scale);
	color.z = sqrt(color.z * scale);
	/*
	color.x *= scale;
	color.y *= scale;
	color.z *= scale;
	*/

	/*
	r = (int)(256.0 * clamp(color.x, 0.0, 0.999));
	ret = r;
	ret <<= 8;
	g = (int)(256.0 * clamp(color.y, 0.0, 0.999));
	ret += g;
	ret <<= 8;
	b = (int)(256.0 * clamp(color.z, 0.0, 0.999));
	ret += b;
	*/
	r = (int)clamp(color.x, 0, 255);
	ret = r;
	ret <<= 8;
	g = (int)clamp(color.y, 0, 255);
	ret += g;
	ret <<= 8;
	b = (int)clamp(color.z, 0, 255);
	ret += b;
	//printf("R %d\t G %d\t B %d\n",r,g,b);
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
