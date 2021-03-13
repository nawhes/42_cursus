/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xzrect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 21:23:49 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				xzrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_xzrect	info;
	double		t;
	double		x;
	double		z;
	t_vec3		outward_normal;

	info = *(t_xzrect *)ob.info;
	t = (info.k - r.orig.y) / r.dir.y;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	x = r.orig.x + t * r.dir.x;
	z = r.orig.z + t * r.dir.z;
	if (x < info.x0 || x > info.x1 || z < info.z0 || z > info.z1)
		return (0);
	rec->u = (x - info.x0) / (info.x1 - info.x0);
	rec->v = (z - info.z0) / (info.z1 - info.z0);
	rec->t_max = t;
	outward_normal = vec(0, 1, 0);
	set_brdf(brdf, r, outward_normal, ray_at(r, t));
	set_brdf2(brdf, ob, info.rgb);
	return (1);
}

t_xzrect		*xzrect(t_xzrect this)
{
	t_xzrect		*node;

	if (!(node = malloc(sizeof(t_xzrect))))
		return (NULL);
	node->x0 = this.x0;
	node->x1 = this.x1;
	node->z0 = this.z0;
	node->z1 = this.z1;
	node->k = this.k;
	node->rgb = this.rgb;
	return (node);
}
