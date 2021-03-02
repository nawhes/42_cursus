/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:23:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 09:13:32 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		ior2fresnel(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * pow((1.0 - cosine), 5));
}

void		transparent(t_brdf *brdf)
{
	double	ior;
	double	costheta;
	double	sintheta;

	ior = brdf->front_face ? (1.0 / brdf->attr) : brdf->attr;
	costheta = fmin(v_dot(brdf->wo, brdf->normal), 1.0);
	sintheta = sqrt(1.0 - costheta * costheta);

	if (ior * sintheta > 1.0 || ior2fresnel(costheta, ior) > random_double())
		brdf->wi = reflect(v_mul(brdf->wo, -1), brdf->normal);
	else
		brdf->wi = refract(v_mul(brdf->wo, -1), brdf->normal, ior);

	brdf->attenuation = v_mul(vec3(1), 0.91339);
	brdf->ray = ray(brdf->point, brdf->wi);
	return ;
}
