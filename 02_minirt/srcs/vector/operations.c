/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:55:49 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 09:16:51 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

t_vec3				vec(double x, double y, double z)
{
	t_vec3			ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3				vec3(double x)
{
	t_vec3			ret;

	ret.x = x;
	ret.y = x;
	ret.z = x;
	return (ret);
}

t_vec3				v_add(t_vec3 a, double b)
{
	a.x += b;
	a.y += b;
	a.z += b;
	return (a);
}

t_vec3				v_add_v(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec3				v_sub(t_vec3 a, double b)
{
	a.x -= b;
	a.y -= b;
	a.z -= b;
	return (a);
}

t_vec3				v_sub_v(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

t_vec3				v_mul(t_vec3 a, double b)
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
	return (a);
}

t_vec3				v_mul_v(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vec3				v_div(t_vec3 a, double b)
{
	a.x /= b;
	a.y /= b;
	a.z /= b;
	return (a);
}

t_vec3				v_div_v(t_vec3 a, t_vec3 b)
{
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
	return (a);
}

t_vec3				v_inv(t_vec3 a)
{
	a.x *= -1;
	a.y *= -1;
	a.z *= -1;
	return (a);
}

double				v_length_sq(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double				v_length(t_vec3 a)
{
	return (sqrt(v_length_sq(a)));
}

double				v_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3				v_cross(t_vec3 a, t_vec3 b)
{
	t_vec3			ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

t_vec3				v_normalize(t_vec3 v)
{
	double			length;

	length = v_length(v);
	v = v_div(v, length);
	return (v);
}

t_vec3				v_random()
{
	t_vec3			ret;

	ret.x = random_double();
	ret.y = random_double();
	ret.z = random_double();
	return (ret);
}

t_vec3				v_random_range(double min, double max)
{
	t_vec3			ret;

	ret.x = random_double_range(min, max);
	ret.y = random_double_range(min, max);
	ret.z = random_double_range(min, max);
	return (ret);
}

t_vec3				v_random_in_unit_sphere()
{
	t_vec3			p;
	while(1)
	{
		p = v_random_range(-1, 1);
		if (v_length_sq(p) >= 1)
			continue;
		return (p);
	}
}

t_vec3				v_random_unit_vector()
{
	return (v_normalize(v_random_in_unit_sphere()));
}

t_vec3				v_random_in_hemisphere(t_vec3 normal)
{
	t_vec3			in_unit_sphere;

	in_unit_sphere = v_random_in_unit_sphere();
	if (v_dot(in_unit_sphere, normal) > 0.0)
		return (in_unit_sphere);
	else
		return (v_mul(in_unit_sphere, -1));
}

int					v_near_zero(t_vec3 vec)
{
	double			e;

	e = 1e-8;
	return ((fabs(vec.x) < e) && (fabs(vec.y) < e) && (fabs(vec.z) < e));
}
