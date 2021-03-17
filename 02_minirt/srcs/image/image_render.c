/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:48:59 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/16 18:15:39 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <pthread.h>

static int		correction(t_vec3 rgb)
{
	int			rgba;

	if (rgb.x != rgb.x)
		rgb.x = 0.0;
	if (rgb.y != rgb.y)
		rgb.y = 0.0;
	if (rgb.z != rgb.z)
		rgb.z = 0.0;
	rgb.x = sqrt(rgb.x);
	rgb.y = sqrt(rgb.y);
	rgb.z = sqrt(rgb.z);
	rgba = (int)(255.0 * clamp(rgb.x, 0.0, 0.999));
	rgba <<= 8;
	rgba += (int)(255.0 * clamp(rgb.y, 0.0, 0.999));
	rgba <<= 8;
	rgba += (int)(255.0 * clamp(rgb.z, 0.0, 0.999));
	return (rgba);
}

static t_vec3	render_pixel(t_minirt *rt, t_viewport *viewport, int x, int y)
{
	int			k;
	double		u;
	double		v;
	t_vec3		rgb;

	k = 0;
	rgb = vec3(0);
	if (ANTIALIAS)
	{
		while (k < SAMPLE_PER_PIXEL)
		{
			u = ((double)x + random_double()) / (rt->r_x - 1);
			v = ((double)y + random_double()) / (rt->r_y - 1);
			rgb = v_add_v(rgb, trace(get_ray(viewport, u, v), rt, MAX_DEPTH));
			k++;
		}
		rgb = v_div(rgb, (double)SAMPLE_PER_PIXEL);
	}
	else
		rgb = trace(get_ray(viewport, (double)x, (double)y), rt, MAX_DEPTH);
	return (rgb);
}

static void		*render_thread(void *param)
{
	int			i;
	int			x;
	int			y;
	t_vec3		rgb;
	t_th_info	*th_info;

	th_info = (t_th_info *)param;
	th_info->vp->set_viewport(th_info->vp, th_info->rt);
	i = 0;
	while (i < th_info->range)
	{
		x = (th_info->offset + i) % th_info->rt->r_x;
		y = (th_info->offset + i) / th_info->rt->r_x;
		rgb = render_pixel(th_info->rt, th_info->vp, x, y);
		image_filter(&rgb, th_info->offset + i,
				th_info->rt->r_x, th_info->rt->r_y);
		th_info->img->rgba[th_info->offset + i] = correction(rgb);
		i++;
	}
	return (NULL);
}

void			image_render(t_minirt *rt, t_image *image, t_viewport *viewport)
{
	pthread_t	threads[NUM_THREAD];
	t_th_info	th_info[NUM_THREAD];
	int			thread;

	thread = 0;
	while (thread < NUM_THREAD)
	{
		th_info[thread].rt = rt;
		th_info[thread].img = image;
		th_info[thread].vp = viewport;
		th_info[thread].offset = rt->pixel * (thread / (double)NUM_THREAD);
		th_info[thread].range = rt->pixel / (double)NUM_THREAD;
		pthread_create(&threads[thread], NULL, render_thread, &th_info[thread]);
		thread++;
	}
	thread = 0;
	while (thread < NUM_THREAD)
	{
		pthread_join(threads[thread], NULL);
		thread++;
	}
}
