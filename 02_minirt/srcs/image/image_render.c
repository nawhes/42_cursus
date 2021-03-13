/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:48:59 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 16:32:37 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		correction(t_vec3 color)
{
	int			rgba;

	if (color.x != color.x)
		color.x = 0.0;
	if (color.y != color.y)
		color.y = 0.0;
	if (color.z != color.z)
		color.z = 0.0;
	if (ANTIALIAS)
		color = v_div(color, (double)SAMPLE_PER_PIXEL);
	color.x = sqrt(color.x);
	color.y = sqrt(color.y);
	color.z = sqrt(color.z);
	rgba = (int)(255.0 * clamp(color.x, 0.0, 0.999));
	rgba <<= 8;
	rgba += (int)(255.0 * clamp(color.y, 0.0, 0.999));
	rgba <<= 8;
	rgba += (int)(255.0 * clamp(color.z, 0.0, 0.999));
	return (rgba);
}

static t_vec3	antialias(t_minirt *rt, t_viewport *viewport, int i, int j)
{
	int			k;
	double		u;
	double		v;
	t_ray		ray;
	t_vec3		rgb;

	k = 0;
	rgb = vec3(0);
	while (k < SAMPLE_PER_PIXEL)
	{
		u = ((double)i + random_double()) / (rt->r_x - 1);
		v = ((double)j + random_double()) / (rt->r_y - 1);
		ray = viewport->get_ray(viewport, u, v);
		rgb = v_add_v(rgb, trace(ray, rt, MAX_DEPTH));
		k++;
	}
	return (rgb);
}

static void		image_render(t_minirt *rt, t_image *image, t_viewport *viewport)
{
	int			i;
	int			x;
	int			y;
	t_ray		ray;
	t_vec3		rgb;

	viewport->set_viewport(viewport, rt);
	i = 0;
	while (i < rt->pixel)
	{
		x = i % rt->r_x;
		y = i / rt->r_x;
		if (ANTIALIAS)
			rgb = antialias(rt, viewport, x, y);
		else
		{
			ray = viewport->get_ray(viewport, (double)x, (double)y);
			rgb = trace(ray, rt, MAX_DEPTH);
		}
		image->rgba[i] = correction(rgb);
		i++;
		if (i % rt->r_x == 0)
			printf("\rRendering.. %d / %d", i, rt->pixel);
	}
}

static t_list	*image_node(t_minirt *rt)
{
	t_image	*p_img;
	t_list	*p_node;

	if (!(p_img = image(rt)))
		error_handle(-3, rt);
	if (!(p_node = ft_lstnew((void *)p_img)))
	{
		free(p_img);
		error_handle(-3, rt);
	}
	return (p_node);
}

void			render(t_minirt *rt)
{
	size_t		i;
	size_t		image_size;
	t_list		*p_image;
	t_list		*p_viewport;

	i = 0;
	image_size = ft_lstsize(rt->p_viewport);
	p_viewport = rt->p_viewport;
	while (i < image_size)
	{
		if (!(p_image = image_node(rt)))
			error_handle(-3, rt);
		ft_lstadd_back(&(rt->p_image), p_image);
		printf("\n** image rendering %lu / %zu\n", i + 1, image_size);
		image_render(rt, p_image->content, p_viewport->content);
		p_image = p_image->next;
		p_viewport = p_viewport->next;
		i++;
	}
	printf("\nRendering complete\n");
}
