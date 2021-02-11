/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:52:31 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/10 04:13:14 by sehpark          ###   ########.fr       */
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

static void		set_viewport(t_viewport *node, t_viewport this)
{
	double		viewport[2];
	t_vec3		u;
	t_vec3		v;
	t_vec3		tmp;

	viewport[0] = 2.0 * tan(degrees_to_radians(this.vfov) / 2);
	viewport[1] = viewport[0] / this.aspect_ratio;
	if (this.lookat.y == 1)
		u = vec3(1, 0, 0);
	else if (this.lookat.y == -1)
		u = vec3(-1, 0, 0);
	else
		u = vec3_cross(vec3(0, 1, 0), this.lookat);
	v = vec3_cross(this.lookat, u);
	node->origin = this.lookfrom;
	node->horizontal = vec3_mul(u, viewport[0]);
	node->vertical = vec3_mul(v, viewport[1]);
	tmp = node->origin;
	tmp = vec3_sub(tmp, vec3_div(node->horizontal, 2));
	tmp = vec3_sub(tmp, vec3_div(node->vertical, 2));
	tmp = vec3_sub(tmp, this.lookat);
	node->lower_left_corner = tmp;
	node->get_ray = viewport_get_ray;
}

t_viewport		*viewport(t_viewport this)
{
	t_viewport	*node;

	if (!(node = malloc(sizeof(t_viewport))))
		return (NULL);
	set_viewport(node, this);
	return (node);
}
