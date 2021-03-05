/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/04 16:36:52 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

int			plane_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_plane	info = *(t_plane *)ob.info;
	double	t;
	double	denom;
	denom = v_dot(info.normal, r.dir);
	if (denom == 0)
		return (0);
	t = (v_dot(info.normal, v_sub_v(info.coord, r.orig))) / denom;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	rec->t_max = t;

	set_brdf(brdf, ob, r, info.normal);
	set_brdf2(brdf, ray_at(r, t));
	return (1);
}

t_plane		*plane(t_plane this)
{
	t_plane	*node;

	if (!(node = malloc(sizeof(t_plane))))
		return (NULL);
	node->coord = this.coord;
	node->normal = v_normalize(this.normal);
	node->rgb = this.rgb;
	return (node);
}
