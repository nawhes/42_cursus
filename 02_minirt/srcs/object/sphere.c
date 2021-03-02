/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:08:38 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void		get_sphere_uv(t_vec3 p, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + PI;
	*u = phi / (2 * PI);
	*v = theta / PI;
}

int			sphere_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_sphere	info = *(t_sphere *)ob.info;
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
	t_vec3	outward_normal;

	oc = v_sub_v(r.orig, info.coord);
	a = v_length_sq(r.dir);
	half_b = v_dot(oc, r.dir);
	c = v_length_sq(oc) - info.diameter * info.diameter;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->t_min || root > rec->t_max)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->t_min || root > rec->t_max)
			return (0);
	}
	rec->t_max = root;
	outward_normal = v_div(v_sub_v(ray_at(r, root), info.coord), info.diameter);
	get_sphere_uv(outward_normal, &rec->u, &rec->v);
	set_brdf(brdf, ob, r, outward_normal);
	set_brdf2(brdf, ray_at(r, root));
	return (1);
}

t_sphere	*sphere(t_sphere this)
{
	t_sphere	*node;

	if (!(node = malloc(sizeof(t_sphere))))
		return (NULL);
	node->coord = this.coord;
	node->diameter = this.diameter;
	node->rgb = this.rgb;
	return (node);
}
