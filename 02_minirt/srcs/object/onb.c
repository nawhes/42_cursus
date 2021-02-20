/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:01:47 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/20 23:11:41 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_onb		onb_build_from_w(t_vec3 n)
{
	t_onb	uvw;
	uvw.w = vec3_unit_vector(n);
	t_vec3	a = (fabs(uvw.w.x) > 0.9) ? vec3(0, 1, 0) : vec3(1, 0, 0);
	uvw.v = vec3_unit_vector(vec3_cross(uvw.w, a));
	uvw.u = vec3_cross(uvw.w, uvw.v);
	return (uvw);
}

t_vec3		onb_local(t_onb uvw, t_vec3 a)
{
	t_vec3	ret;

	uvw.u = vec3_mul(uvw.u, a.x);
	uvw.v = vec3_mul(uvw.v, a.y);
	uvw.w = vec3_mul(uvw.w, a.z);

	ret = vec3_add(vec3_add(uvw.u, uvw.v),uvw.w);
	return (ret);
}

double		onb_value(t_onb uvw, t_vec3 dir)
{
	double	cosine;
	cosine = vec3_dot(vec3_unit_vector(dir), uvw.w);
	if (cosine <= 0)
		return (0);
	return (cosine / PI);
}
