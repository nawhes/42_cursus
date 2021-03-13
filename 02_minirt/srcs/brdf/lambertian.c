/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 20:31:57 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		lambert_eval(t_brdf brdf, t_vec3 wi)
{
	double	costheta;

	costheta = v_dot(wi, brdf.normal);
	if (costheta <= 0)
		return (vec3(0));
	return (v_div(v_mul(brdf.albedo, costheta * 2.0), M_PI));
}

void		lambertian(t_brdf *brdf)
{
	t_onb	uvw;

	uvw = onb_build_from_w(brdf->normal);
	brdf->wi = v_normalize(onb_local(uvw, random_cosine_direction()));
	brdf->ray = ray(brdf->point, brdf->wi);
	brdf->attenuation = lambert_eval(*brdf, brdf->wi);
	return ;
}
