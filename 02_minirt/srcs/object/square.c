/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:22:20 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/14 02:09:59 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		intersection_sq(t_vec3 center_to_p, t_square info)
{
	t_onb		uvw;
	double		costheta_width;
	double		costheta_height;
	double		limit_width;
	double		limit_height;

	uvw = onb_build_from_w(info.normal);
	costheta_width = fabs(v_dot(uvw.u, v_normalize(center_to_p)));
	costheta_height = fabs(v_dot(uvw.v, v_normalize(center_to_p)));
	limit_width = (info.side_size / 2.0) / costheta_width;
	limit_height = (info.side_size / 2.0) / costheta_height;
	if (v_length(center_to_p) > limit_width)
		return (0);
	if (v_length(center_to_p) > limit_height)
		return (0);
	return (1);
}

int				square_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_square	info;
	double		t;
	double		ndotdir;

	info = *(t_square *)ob.info;
	ndotdir = v_dot(info.normal, r.dir);
	if (ndotdir == 0)
		return (0);
	t = (v_dot(info.normal, v_sub_v(info.coord, r.orig))) / ndotdir;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	if (!intersection_sq(v_sub_v(info.coord, ray_at(r, t)), info))
		return (0);
	rec->t_max = t;
	set_brdf(brdf, r, info.normal, ray_at(r, t));
	set_brdf2(brdf, ob, info.rgb);
	return (1);
}

t_square		*square(t_square this)
{
	t_square		*node;

	if (!(node = malloc(sizeof(t_square))))
		return (NULL);
	node->coord = this.coord;
	node->normal = v_normalize(this.normal);
	node->side_size = this.side_size;
	node->rgb = this.rgb;
	return (node);
}
