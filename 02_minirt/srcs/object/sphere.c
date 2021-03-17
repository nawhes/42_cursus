/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/18 00:20:36 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/*
** https://raytracing.github.io/books/RayTracingInOneWeekend.html
** #surfacenormalsandmultipleobjects/simplifyingtheray-sphereintersectioncode
*/

void			get_sphere_uv(t_vec3 p, double *u, double *v)
{
	double		theta;
	double		phi;

	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + M_PI;
	*u = phi / (2.0 * M_PI);
	*v = theta / M_PI;
}

static int		intersection_sp(
		t_ray r,
		t_record *rec,
		t_sphere info,
		double *t)
{
	t_vec3		oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;

	oc = v_sub_v(r.orig, info.coord);
	a = v_length_sq(r.dir);
	half_b = v_dot(oc, r.dir);
	c = v_length_sq(oc) - info.radius * info.radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	discriminant = sqrt(discriminant);
	*t = (-half_b - discriminant) / a;
	if (*t < rec->t_min || *t > rec->t_max)
	{
		*t = (-half_b + discriminant) / a;
		if (*t < rec->t_min || *t > rec->t_max)
			return (0);
	}
	return (1);
}

int				sphere_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_sphere	info;
	double		t;
	t_vec3		outward_normal;

	info = *(t_sphere *)ob.info;
	if (!intersection_sp(r, rec, info, &t))
		return (0);
	rec->t_max = t;
	outward_normal = v_div(v_sub_v(ray_at(r, t), info.coord), info.radius);
	get_sphere_uv(outward_normal, &rec->u, &rec->v);
	set_brdf(brdf, r, outward_normal, ray_at(r, t));
	set_brdf2(brdf, ob, info.rgb);
	return (1);
}

t_sphere		*sphere(t_sphere this)
{
	t_sphere	*node;

	if (!(node = malloc(sizeof(t_sphere))))
		return (NULL);
	node->coord = this.coord;
	node->radius = this.radius;
	node->rgb = this.rgb;
	return (node);
}
