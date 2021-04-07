/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:23:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/04/07 21:32:10 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** https://raytracing.github.io/books/RayTracingInOneWeekend.html#dielectrics
*/

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
	costheta = fmin(v_dot(v_inv(brdf->wo), brdf->normal), 1.0);
	sintheta = sqrt(1.0 - costheta * costheta);
	if (ior * sintheta > 1.0 || ior2fresnel(costheta, ior) > random_double())
		brdf->wi = reflect(brdf->wo, brdf->normal);
	else
		brdf->wi = refract(brdf->wo, brdf->normal, ior);
	brdf->attenuation = v_mul(vec3(1), 0.91339);
	brdf->ray = ray(brdf->point, brdf->wi);
	return ;
}
