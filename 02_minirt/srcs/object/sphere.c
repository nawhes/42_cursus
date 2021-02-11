/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 22:20:39 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/04 02:05:30 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"
#include "viewport.h"

#include "object.h"
#include <math.h>
#include <stdlib.h>

void		get_sphere_uv(t_vec3 p, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = acos(-p.y);
	phi = atan2(-p.z, p.x) + PI;
	*u = phi / (2 * PI);
	*v = theta / PI;
}

int			sphere_hit(
		t_object ob, t_ray *r, t_hit_record *rec)
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

	oc = vec3_sub(r->orig, info.coord);
	a = vec3_length_square(r->dir);
	half_b = vec3_dot(oc, r->dir);
	c = vec3_length_square(oc) - info.diameter * info.diameter;
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
	rec->t = root;
	rec->p = ray_at(*r, rec->t);
	rec->t_max = rec->t;
	outward_normal = vec3_div(vec3_sub(rec->p, info.coord), info.diameter);
	rec->set_face_normal(rec, r, &outward_normal);
	get_sphere_uv(outward_normal, &rec->u, &rec->v);

	// 요기부터
	if (ob.texture == LAMBERTIAN)
	{
		rec->scatter = lambertian_scatter;
		rec->emitted = vec3(0, 0, 0);
		rec->rgb = info.rgb;
	}
	if (ob.texture == METAL)
	{
		rec->scatter = metal_scatter;
		rec->emitted = vec3(0, 0, 0);
		rec->rgb = info.rgb;
	}
	if (ob.texture == DIELECTRIC)
	{
		rec->scatter = dielectric_scatter;
		rec->emitted = vec3(0, 0, 0);
		rec->rgb = info.rgb;
	}
	if (ob.texture == DIFFUSE_LIGHT)
	{
		rec->scatter = NULL;
		rec->emitted = info.rgb;
		rec->rgb = info.rgb;
	}
	if (ob.texture == CHECK_BOX)
	{
		rec->scatter = lambertian_scatter;
		rec->emitted = vec3(0, 0, 0);
		double sines;
		sines = sin(10 * rec->p.x) * sin(10 * rec->p.y) * sin(10 * rec->p.z);
		if (sines < 0)
			rec->rgb = vec3(0.2, 0.3, 0.1);
		else
			rec->rgb = vec3(0.9, 0.9, 0.9);
	}
	// 요기까지
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
