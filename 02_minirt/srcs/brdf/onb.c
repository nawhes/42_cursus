/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   onb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:01:47 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/04 19:13:44 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_onb		onb_build_from_w(t_vec3 n)
{
	t_onb	uvw;
	uvw.w = v_normalize(n);
	t_vec3	a = (fabs(uvw.w.x) > 0.99) ? vec(0, 1, 0) : vec(1, 0, 0);
	uvw.v = v_normalize(v_cross(uvw.w, a));
	uvw.u = v_cross(uvw.w, uvw.v);
	return (uvw);
}

t_onb		onb_build_from_v(t_vec3 n)
{
	t_onb	uvw;
	uvw.v = v_normalize(n);
	t_vec3	a = fabs(v_dot(n, vec(0, 1, 0))) > 0.99 ? vec(0, 0, 1) : vec(0, 1, 0);
	uvw.u = v_normalize(v_cross(uvw.v, a));
	uvw.w = v_cross(uvw.u, uvw.v);
	return (uvw);
}

t_onb		onb_build_from_u(t_vec3 n)
{
	t_onb	uvw;
	uvw.u = v_normalize(n);
	t_vec3	a = (fabs(uvw.u.x) > 0.99) ? vec(0, 1, 0) : vec(1, 0, 0);
	uvw.w = v_normalize(v_cross(uvw.u, a));
	uvw.v = v_cross(uvw.w, uvw.u);
	return (uvw);
}

t_vec3		onb_local(t_onb uvw, t_vec3 a)
{
	t_vec3	ret;

	uvw.u = v_mul(uvw.u, a.x);
	uvw.v = v_mul(uvw.v, a.y);
	uvw.w = v_mul(uvw.w, a.z);
	ret = v_add_v(v_add_v(uvw.u, uvw.v),uvw.w);
	return (ret);
}
