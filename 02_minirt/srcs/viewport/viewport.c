/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:52:31 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/17 20:55:00 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "viewport.h"
#include "tools.h"
#include <math.h>

t_ray			viewport_get_ray(t_viewport viewport, double s, double t)
{
	t_vec3		dir;
	
	dir = viewport.lower_left_corner;
	dir = vec3_add(dir, vec3_mul(viewport.horizontal, s));
	dir = vec3_add(dir, vec3_mul(viewport.vertical, t));
	dir = vec3_sub(dir, viewport.origin);
	return (ray_construct(viewport.origin, dir));
}

t_viewport		*viewport_init
(t_vec3 lookfrom, t_vec3 lookat, double vfov, double aspect_ratio)
{
	t_viewport	*viewport;
	double		theta;
	double		h;
	double		viewport_width;
	double		viewport_height;

	if (!(viewport = malloc(sizeof(t_viewport))))
		return NULL;
	theta = degrees_to_radians(vfov);
	h = tan(theta / 2);
	
	viewport_height = 2.0 * h;
	viewport_width = aspect_ratio * viewport_height;

	t_vec3		w = vec3_unit_vector(vec3_sub(lookfrom, lookat));
	t_vec3		u = vec3_unit_vector(vec3_cross(vec3(0, 1, 0), w));
	t_vec3		v = vec3_cross(w, u);

	viewport->origin = lookfrom;
	viewport->horizontal = vec3_mul(u, viewport_width);
	viewport->vertical = vec3_mul(v, viewport_height);
	
	t_vec3		tmp;
	tmp = viewport->origin;
	tmp = vec3_sub(tmp, vec3_div(viewport->horizontal, 2));
	tmp = vec3_sub(tmp, vec3_div(viewport->vertical, 2));
	tmp = vec3_sub(tmp, w);
	viewport->lower_left_corner = tmp;
	viewport->get_ray = viewport_get_ray;
	return (viewport);
}
