/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_random.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:55:49 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:49:13 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

t_vec3				v_random(void)
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

t_vec3				v_random_in_unit_sphere(void)
{
	t_vec3			p;

	while (1)
	{
		p = v_random_range(-1, 1);
		if (v_length_sq(p) >= 1)
			continue;
		return (p);
	}
}

t_vec3				v_random_unit_vector(void)
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
