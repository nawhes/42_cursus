/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:22:20 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 21:22:58 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		is_in(t_vec3 edge, t_vec3 vp, t_vec3 normal)
{
	if (v_dot(normal, v_cross(edge, vp)) < 0)
		return (0);
	return (1);
}

static t_vec3	get_normal(t_triangle info)
{
	t_vec3		normal;
	t_vec3		p1p2;
	t_vec3		p1p3;

	p1p2 = v_sub_v(info.point2, info.point1);
	p1p3 = v_sub_v(info.point3, info.point1);
	normal = v_normalize(v_cross(p1p2, p1p3));
	return (normal);
}

static int		intersection_tr(t_triangle info, t_vec3 p, t_vec3 normal)
{
	if (!is_in(v_sub_v(info.point2, info.point1), v_sub_v(p, info.point1),
				normal))
		return (0);
	if (!is_in(v_sub_v(info.point3, info.point2), v_sub_v(p, info.point2),
				normal))
		return (0);
	if (!is_in(v_sub_v(info.point1, info.point3), v_sub_v(p, info.point3),
				normal))
		return (0);
	return (1);
}

int				triangle_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_triangle	info;
	double		t;
	double		ndotdir;
	t_vec3		normal;

	info = *(t_triangle *)ob.info;
	normal = get_normal(info);
	ndotdir = v_dot(normal, r.dir);
	if (ndotdir == 0)
		return (0);
	t = (v_dot(normal, v_sub_v(info.point1, r.orig))) / ndotdir;
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	if (!intersection_tr(info, ray_at(r, t), normal))
		return (0);
	rec->t_max = t;
	set_brdf(brdf, r, normal, ray_at(r, t));
	set_brdf2(brdf, ob, info.rgb);
	return (1);
}

t_triangle		*triangle(t_triangle this)
{
	t_triangle	*node;

	if (!(node = malloc(sizeof(t_triangle))))
		return (NULL);
	node->point1 = this.point1;
	node->point2 = this.point2;
	node->point3 = this.point3;
	node->rgb = this.rgb;
	return (node);
}
