/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyrect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:34:53 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int				xyrect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_xyrect	info;
	double		t;
	double		x;
	double		y;
	t_vec3		outward_normal;

	info = *(t_xyrect *)ob.info;
	t = (info.k - r.orig.z) / r.dir.z;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	x = r.orig.x + t * r.dir.x;
	y = r.orig.y + t * r.dir.y;
	if (x < info.x0 || x > info.x1 || y < info.y0 || y > info.y1)
		return (0);
	rec->u = (x - info.x0) / (info.x1 - info.x0);
	rec->v = (y - info.y0) / (info.y1 - info.y0);
	rec->t_max = t;
	outward_normal = vec(0, 0, 1);
	set_brdf(brdf, ob, r, outward_normal);
	set_brdf2(brdf, ray_at(r, t), info.rgb);
	return (1);
}

t_xyrect		*xyrect(t_xyrect this)
{
	t_xyrect	*node;

	if (!(node = malloc(sizeof(t_xyrect))))
		return (NULL);
	node->x0 = this.x0;
	node->x1 = this.x1;
	node->y0 = this.y0;
	node->y1 = this.y1;
	node->k = this.k;
	node->rgb = this.rgb;
	return (node);
}
