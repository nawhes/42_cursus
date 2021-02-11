/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yzrect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/12 03:48:09 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "viewport.h"

#include "object.h"
#include <math.h>
#include <stdlib.h>

int			yzrect_hit(t_object ob, t_ray *r, t_hit_record *rec)
{
	t_yzrect	info = *((t_yzrect *)ob.info);
	double	t;
	double	y;
	double	z;
	t_vec3	outward_normal;

	t = (info.k - r->orig.x) / r->dir.x;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	y = r->orig.y + t * r->dir.y;
	z = r->orig.z + t * r->dir.z;
	if (y < info.y0 || y > info.y1 || z < info.z0 || z > info.z1)
		return (0);
	rec->u = (y - info.y0) / (info.y1 - info.y0);
	rec->v = (z - info.z0) / (info.z1 - info.z0);
	rec->t = t;
	outward_normal = vec3(1, 0, 0);
	
	rec->p = ray_at(*r, rec->t);
	rec->t_max = rec->t;
	rec->set_face_normal(rec, r, &outward_normal);
	set_record(ob, rec, info.rgb);
	return (1);
}

t_yzrect		*yzrect(t_yzrect this)
{
	t_yzrect		*node;

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
