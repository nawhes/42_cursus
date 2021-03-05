/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:52:31 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/04 20:02:34 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_ray			viewport_get_ray(t_viewport vp, double s, double t)
{
	t_vec3		dir;
	
	dir = vp.lower_left_corner;
	dir = v_add_v(dir, v_mul(vp.horizontal, s));
	dir = v_add_v(dir, v_mul(vp.vertical, t));
	dir = v_sub_v(dir, vp.origin);
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
	this.lookat = v_normalize(this.lookat);
	if (this.lookat.y == 1)
		u = vec(1, 0, 0);
	else if (this.lookat.y == -1)
		u = vec(-1, 0, 0);
	else
		u = v_cross(vec(0, 1, 0), this.lookat);
	v = v_cross(this.lookat, u);
	node->origin = this.lookfrom;
	node->horizontal = v_mul(u, viewport[0]);
	node->vertical = v_mul(v, viewport[1]);
	tmp = node->origin;
	tmp = v_sub_v(tmp, v_div(node->horizontal, 2));
	tmp = v_sub_v(tmp, v_div(node->vertical, 2));
	tmp = v_sub_v(tmp, this.lookat);
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
