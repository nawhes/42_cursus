/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:22:20 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/06 06:21:54 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	intersection_rect(t_vec3 center_to_p, t_rect info)
{
	t_onb	uvw;
	double	costheta_width;
	double	costheta_height;
	double	limit_width;
	double	limit_height;

	uvw = onb_build_from_w(info.normal);
	costheta_width = fabs(v_dot(uvw.u, v_normalize(center_to_p)));
	costheta_height = fabs(v_dot(uvw.v, v_normalize(center_to_p)));
	limit_width = (info.width / 2.0) / costheta_width;
	limit_height = (info.height / 2.0) / costheta_height;
	if (v_length(center_to_p) > limit_width)
		return (0);
	if (v_length(center_to_p) > limit_height)
		return (0);
	return (1);
}

int			rect_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_rect	info = *(t_rect *)ob.info;
	double	t;
	double	ndotdir;

	ndotdir = v_dot(info.normal, r.dir);
	if (ndotdir == 0)
		return (0);
	t = (v_dot(info.normal, v_sub_v(info.coord, r.orig))) / ndotdir;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	if (!intersection_rect(v_sub_v(info.coord, ray_at(r, t)), info))
		return (0);
	rec->t_max = t;
	set_brdf(brdf, ob, r, info.normal);
	set_brdf2(brdf, ray_at(r, t));
	return (1);
}

t_rect		*rect(t_rect this)
{
	t_rect		*node;

	if (!(node = malloc(sizeof(t_rect))))
		return (NULL);
	node->coord = this.coord;
	node->normal = v_normalize(this.normal);
	node->width = this.width;
	node->height = this.height;
	node->rgb = this.rgb;
	return (node);
}
