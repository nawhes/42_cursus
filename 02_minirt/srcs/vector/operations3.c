/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:55:49 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:44:39 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

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

double				v_length_sq(t_vec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double				v_length(t_vec3 a)
{
	return (sqrt(v_length_sq(a)));
}
