/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:31:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 20:31:45 by sehpark          ###   ########.fr       */
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
