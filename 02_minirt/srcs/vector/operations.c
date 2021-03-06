/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:55:49 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:42:30 by sehpark          ###   ########.fr       */
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

t_vec3				v_normalize(t_vec3 v)
{
	double			length;

	length = v_length(v);
	v = v_div(v, length);
	return (v);
}

int					v_near_zero(t_vec3 vec)
{
	double			e;

	e = 1e-8;
	return ((fabs(vec.x) < e) && (fabs(vec.y) < e) && (fabs(vec.z) < e));
}
