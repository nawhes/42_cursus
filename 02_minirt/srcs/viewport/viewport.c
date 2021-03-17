/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:52:31 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/16 18:08:12 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_ray			get_ray(t_viewport *vp, double s, double t)
{
	t_vec3		dir;

	dir = vp->upper_left_corner;
	dir = v_add_v(dir, v_mul(vp->horizontal, s));
	dir = v_sub_v(dir, v_mul(vp->vertical, t));
	dir = v_sub_v(dir, vp->origin);
	return (ray(vp->origin, dir));
}

static void		vp_set_viewport(t_viewport *vp, t_minirt *rt)
{
	double		viewport[2];
	t_vec3		u;
	t_vec3		v;
	t_vec3		tmp;
	double		aspect_ratio;

	aspect_ratio = (double)rt->r_x / (double)rt->r_y;
	viewport[0] = 2.0 * tan(degrees_to_radians(vp->vfov) / 2.0);
	viewport[1] = viewport[0] / aspect_ratio;
	vp->lookat = v_normalize(vp->lookat);
	if (vp->lookat.y == 1.0)
		u = vec(1, 0, 0);
	else if (vp->lookat.y == -1.0)
		u = vec(-1, 0, 0);
	else
		u = v_cross(vec(0, 1, 0), vp->lookat);
	v = v_cross(vp->lookat, u);
	vp->origin = vp->lookfrom;
	vp->horizontal = v_mul(u, viewport[0]);
	vp->vertical = v_mul(v, viewport[1]);
	tmp = v_sub_v(vp->origin, v_div(vp->horizontal, 2));
	tmp = v_add_v(tmp, v_div(vp->vertical, 2));
	tmp = v_sub_v(tmp, vp->lookat);
	vp->upper_left_corner = tmp;
}

t_viewport		*viewport(t_viewport this)
{
	t_viewport	*node;

	if (!(node = malloc(sizeof(t_viewport))))
		return (NULL);
	node->lookfrom = this.lookfrom;
	node->lookat = this.lookat;
	node->vfov = this.vfov;
	node->set_viewport = vp_set_viewport;
	return (node);
}
