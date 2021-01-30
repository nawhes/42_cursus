/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:52:31 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 06:18:07 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "viewport.h"
#include "tools.h"
#include <math.h>

t_ray			viewport_get_ray(t_viewport vp, double s, double t)
{
	t_vec3		dir;
	
	dir = vp.lower_left_corner;
	dir = vec3_add(dir, vec3_mul(vp.horizontal, s));
	dir = vec3_add(dir, vec3_mul(vp.vertical, t));
	dir = vec3_sub(dir, vp.origin);
	return (ray(vp.origin, dir));
}

t_viewport		*viewport(t_viewport this)
{
	t_viewport	*node;
	double		theta;
	double		h;
	double		viewport_width;
	double		viewport_height;

	if (!(node = malloc(sizeof(t_viewport))))
		return (NULL);
	theta = degrees_to_radians(this.vfov);
	h = tan(theta / 2);
	
	viewport_height = 2.0 * h;
	viewport_width = this.aspect_ratio * viewport_height;

	t_vec3		w = vec3_unit_vector(vec3_sub(this.lookfrom, this.lookat));
	t_vec3		u = vec3_unit_vector(vec3_cross(vec3(0, 1, 0), w));
	t_vec3		v = vec3_cross(w, u);

	node->origin = this.lookfrom;
	node->horizontal = vec3_mul(u, viewport_width);
	node->vertical = vec3_mul(v, viewport_height);
	
	t_vec3		tmp;
	tmp = node->origin;
	tmp = vec3_sub(tmp, vec3_div(node->horizontal, 2));
	tmp = vec3_sub(tmp, vec3_div(node->vertical, 2));
	tmp = vec3_sub(tmp, w);
	node->lower_left_corner = tmp;
	node->get_ray = viewport_get_ray;
	return (node);
}
