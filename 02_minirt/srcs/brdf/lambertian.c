/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:27:42 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		random_cosine_direction()
{
	double	r1 = random_double();
	double	r2 = random_double();
	double	phi = 2 * PI * r1;
	double	z = sqrt(1 - r2);
	double	x = cos(phi) * sqrt(r2);
	double	y = sin(phi) * sqrt(r2);
	return (vec(x, y, z));
}

t_vec3		lambert_eval(t_brdf brdf, t_vec3 wi)
{
	double	costheta = v_dot(wi, brdf.normal);
	if (costheta <= 0)
		return (vec3(0));
	return (v_div(v_mul(brdf.albedo, costheta * 2.0), PI));
}

void		lambertian(t_brdf *brdf)
{
	t_onb	uvw;

	//sample
	uvw = onb_build_from_w(brdf->normal);
	brdf->wi = v_normalize(onb_local(uvw, random_cosine_direction()));
	brdf->ray = ray(brdf->point, brdf->wi);

	//eval
	brdf->attenuation = lambert_eval(*brdf, brdf->wi);
	return ;
}
