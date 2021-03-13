/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 07:54:32 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:18:58 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	random_to_sphere(double radius, double distance_squared)
{
	double		r1;
	double		r2;
	double		phi;
	t_vec3		dir;

	r1 = random_double();
	r2 = random_double();
	phi = 2.0 * M_PI * r1;
	dir.z = 1.0 + r2 * (sqrt(1.0 - radius * radius / distance_squared) - 1.0);
	dir.x = cos(phi) * sqrt(1.0 - dir.z * dir.z);
	dir.y = sin(phi) * sqrt(1.0 - dir.z * dir.z);
	return (dir);
}

t_vec3			sphere_random(t_sphere *sp, t_vec3 o)
{
	t_vec3		direction;
	double		distance_squared;
	t_onb		uvw;

	direction = v_sub_v(sp->coord, o);
	distance_squared = v_length_sq(direction);
	uvw = onb_build_from_w(direction);
	return (onb_local(uvw, random_to_sphere(sp->radius, distance_squared)));
}

t_vec3			random_cosine_direction(void)
{
	t_vec3		dir;
	double		r1;
	double		r2;
	double		phi;

	r1 = random_double();
	r2 = random_double();
	phi = 2.0 * M_PI * r1;
	dir.x = cos(phi) * sqrt(r2);
	dir.y = sin(phi) * sqrt(r2);
	dir.z = sqrt(1.0 - r2);
	return (dir);
}

t_vec3			random_microfacet_direction(double roughness)
{
	t_vec3		dir;
	double		r[2];
	double		a2;
	double		theta;
	double		phi;

	r[0] = random_double();
	r[1] = random_double();
	a2 = roughness * roughness;
	theta = acos(sqrt((1.0 - r[0]) / ((a2 - 1.0) * r[0] + 1.0)));
	phi = 2.0 * M_PI * r[1];
	dir.x = sin(theta) * cos(phi);
	dir.y = sin(theta) * sin(phi);
	dir.z = cos(theta);
	return (dir);
}
