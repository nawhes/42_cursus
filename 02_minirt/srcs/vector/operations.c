/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:55:49 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/16 06:51:27 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "struct.h"
#include "tools.h"

t_vec3				vec3(double x, double y, double z)
{
	t_vec3			ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3				vec3_add(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec3				vec3_sub(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec3				vec3_mul(t_vec3 a, double b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return (a);
}

t_vec3				vec3_mul_vec3(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vec3				vec3_div(t_vec3 a, double b)
{
	a.x *= 1 / b;
	a.y *= 1 / b;
	a.z *= 1 / b;
	return (a);
}

double				vec3_length_square(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double				vec3_length(t_vec3 a)
{
	return (sqrt(vec3_length_square(a)));
}

double				vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3				vec3_cross(t_vec3 a, t_vec3 b)
{
	t_vec3			ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

t_vec3				vec3_unit_vector(t_vec3 v)
{
	double			length;

	length = vec3_length(v);
	v = vec3_div(v, length);
	return (v);
}

t_vec3				vec3_random()
{
	t_vec3			ret;

	ret.x = random_double();
	ret.y = random_double();
	ret.z = random_double();
	return (ret);
}

t_vec3				vec3_random_range(double min, double max)
{
	t_vec3			ret;

	ret.x = random_double_range(min, max);
	ret.y = random_double_range(min, max);
	ret.z = random_double_range(min, max);
	return (ret);
}

t_vec3				vec3_random_in_unit_sphere()
{
	t_vec3			p;
	while(1)
	{
		p = vec3_random_range(-1, 1);
		if (vec3_length_square(p) >= 1)
			continue;
		return (p);
	}
}

t_vec3				vec3_random_unit_vector()
{
	return (vec3_unit_vector(vec3_random_in_unit_sphere()));
}

int					vec3_near_zero(t_vec3 vec)
{
	double			e;

	e = 1e-8;
	return ((fabs(vec.x) < e) && (fabs(vec.y) < e) && (fabs(vec.z) < e));
}

t_vec3				reflect(t_vec3 v, t_vec3 n)
{
	double			tmp;

	tmp = vec3_dot(v, n) * 2;
	return (vec3_sub(v, vec3_mul(n, tmp)));
}

t_vec3				refract(t_vec3 uv, t_vec3 n, double etai_over_etat)
{
	double			cos_theta;
	t_vec3			r_out_perp;
	t_vec3			r_out_parallel;

	cos_theta = fmin(vec3_dot(vec3_mul(uv, -1), n), 1.0);
	r_out_perp = vec3_mul(vec3_add(uv, vec3_mul(n, cos_theta)), etai_over_etat);
	r_out_parallel = vec3_mul(n, -sqrt(fabs(1.0 - vec3_length_square(r_out_perp))));
	return (vec3_add(r_out_perp, r_out_parallel));
}
