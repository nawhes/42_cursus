/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yzrect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 21:23:55 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				yzrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_yzrect	info;
	double		t;
	double		y;
	double		z;
	t_vec3		outward_normal;

	info = *(t_yzrect *)ob.info;
	t = (info.k - r.orig.x) / r.dir.x;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	y = r.orig.y + t * r.dir.y;
	z = r.orig.z + t * r.dir.z;
	if (y < info.y0 || y > info.y1 || z < info.z0 || z > info.z1)
		return (0);
	rec->u = (y - info.y0) / (info.y1 - info.y0);
	rec->v = (z - info.z0) / (info.z1 - info.z0);
	rec->t_max = t;
	outward_normal = vec(1, 0, 0);
	set_brdf(brdf, r, outward_normal, ray_at(r, t));
	set_brdf2(brdf, ob, info.rgb);
	return (1);
}

t_yzrect		*yzrect(t_yzrect this)
{
	t_yzrect	*node;

	if (!(node = malloc(sizeof(t_yzrect))))
		return (NULL);
	node->y0 = this.y0;
	node->y1 = this.y1;
	node->z0 = this.z0;
	node->z1 = this.z1;
	node->k = this.k;
	node->rgb = this.rgb;
	return (node);
}
