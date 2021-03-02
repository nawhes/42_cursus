/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 07:54:32 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:51:18 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3				reflect(t_vec3 v, t_vec3 n)
{
	double			tmp;

	tmp = v_dot(v, n) * 2;
	return (v_sub_v(v, v_mul(n, tmp)));
}

t_vec3				refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double			cos_theta;
	t_vec3			r_out_perp;
	t_vec3			r_out_parallel;

	cos_theta = fmin(v_dot(v_mul(uv, -1), n), 1.0);
	r_out_perp = v_mul(v_add_v(uv, v_mul(n, cos_theta)), etai_over_etat);
	r_out_parallel = v_mul(n, -sqrt(fabs(1.0 - v_length_sq(r_out_perp))));
	return (v_add_v(r_out_perp, r_out_parallel));
}

static t_vec3	random_to_sphere(double radius, double distance_squared)
{
	double	r1 = random_double();
	double	r2 = random_double();
	double	z = 1 + r2 * (sqrt(1 - radius * radius / distance_squared) - 1);

	double	phi = 2 * PI * r1;
	double	x = cos(phi) * sqrt(1 - z * z);
	double	y = sin(phi) * sqrt(1 - z * z);

	return (vec(x, y, z));
}

t_vec3		sphere_random(t_sphere *sp, t_vec3 o)
{
	t_vec3	direction = v_sub_v(sp->coord, o);
	double	distance_squared = v_length_sq(direction);
	t_onb	uvw;
	uvw = onb_build_from_w(direction);
	return (onb_local(uvw, random_to_sphere(sp->diameter, distance_squared)));
}
