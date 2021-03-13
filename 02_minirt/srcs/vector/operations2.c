/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:55:49 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:43:31 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

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
