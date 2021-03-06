/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:22:20 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/18 00:17:33 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** https://www.shadertoy.com/view/Md3cWj
*/

static int		intersection_cy3(t_cy cy, t_vec3 *normal, double *t)
{
	double		ddotn;
	double		odotn;
	double		front2;

	ddotn = v_dot(cy.d, cy.normal);
	odotn = v_dot(cy.o, cy.normal);
	if (ddotn < 0)
	{
		cy.normal = v_inv(cy.normal);
		ddotn = -ddotn;
		odotn = -odotn;
	}
	front2 = (-cy.l - odotn) / ddotn;
	if (front2 > cy.front)
	{
		cy.front = front2;
		*normal = v_inv(cy.normal);
	}
	if (cy.front > cy.back || odotn + ddotn * cy.front > cy.l)
		return (0);
	*t = cy.front;
	return (1);
}

static int		intersection_cy2(t_cy cy, t_vec3 *normal, double *t)
{
	double		rdotp;
	double		pdotp;
	double		q;
	double		discriminant;

	rdotp = v_dot(cy.r, cy.p);
	pdotp = v_dot(cy.p, cy.p);
	q = pdotp - rdotp * rdotp;
	if (q >= cy.radius * cy.radius)
		return (0);
	discriminant = sqrt(cy.radius * cy.radius - q);
	cy.front = (-rdotp - discriminant) / cy.rl;
	cy.back = (-rdotp + discriminant) / cy.rl;
	*normal = v_normalize(v_add_v(cy.p, v_mul(cy.r, cy.front * cy.rl)));
	return (intersection_cy3(cy, normal, t));
}

static int		intersection_cy(
		t_ray r_in,
		t_cylinder info,
		t_vec3 *normal,
		double *t)
{
	t_vec3		mid;
	t_cy		cy;

	cy.top = v_add_v(info.coord, v_mul(info.normal, info.height));
	cy.bottom = info.coord;
	mid = v_div(v_add_v(cy.bottom, cy.top), 2.0);
	cy.o = v_sub_v(r_in.orig, mid);
	cy.d = r_in.dir;
	cy.radius = info.radius;
	cy.normal = v_div(v_sub_v(cy.bottom, cy.top), 2.0);
	cy.l = v_length(cy.normal);
	cy.normal = v_normalize(cy.normal);
	cy.r = v_sub_v(cy.d, v_mul(cy.normal, v_dot(cy.d, cy.normal)));
	cy.rl = v_length(cy.r);
	cy.r = v_normalize(cy.r);
	cy.p = v_sub_v(cy.o, v_mul(cy.normal, v_dot(cy.o, cy.normal)));
	return (intersection_cy2(cy, normal, t));
}

int				cylinder_hit(t_object ob, t_ray r, t_record *rec, t_brdf *brdf)
{
	t_cylinder	info;
	t_vec3		normal;
	double		t;

	info = *(t_cylinder *)ob.info;
	if (!intersection_cy(r, info, &normal, &t))
		return (0);
	if (t < rec->t_min || t > rec->t_max)
		return (0);
	rec->t_max = t;
	set_brdf(brdf, r, normal, ray_at(r, t));
	set_brdf2(brdf, ob, info.rgb);
	return (1);
}

t_cylinder		*cylinder(t_cylinder this)
{
	t_cylinder		*node;

	if (!(node = malloc(sizeof(t_cylinder))))
		return (NULL);
	node->coord = this.coord;
	node->normal = v_normalize(this.normal);
	node->radius = this.radius;
	node->height = this.height;
	node->rgb = this.rgb;
	return (node);
}
