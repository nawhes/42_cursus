/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 04:08:17 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			dielectric(t_ray r, t_hit_record *rec)
{
	t_onb	uvw;
	uvw = onb_build_from_w(rec->normal);
	t_vec3	wo = vec3_unit_vector(vec3_mul(r.dir, -1));
	t_vec3	normal = rec->normal;
	wo = onb_local(uvw, wo);
	normal = onb_local(uvw, normal);



//	double	ior = rec->attr;
	double	ior = 1.5;
	//sample
	double	costheta = vec3_dot(normal, wo);
	double	eta;
	t_vec3	wi;
	if (rec->front_face)
	{
		eta = ior / 1;
//		normal = vec3_mul(normal, -1);
	}
	else
	{
		costheta = -costheta;
		eta = 1 / ior;
	}
	double	k = 1 - eta * eta * (1 - costheta * costheta);
	if (k < 0)
		wi = reflect(wo, rec->normal);
	else
		wi = refract(wo, normal, eta);
	/*
	{
		wi = vec3_mul(wo, eta);
		wi = vec3_add(wi, vec3_mul(normal, eta*costheta - sqrt(k)));
		wi = vec3_unit_vector(wi);
	}
	*/
	uvw = onb_build_from_w(rec->normal);
	wi = onb_local(uvw, wi);
	rec->ray = ray(rec->p, wi);

	//pdf


	//eval
	rec->attenuation = vec3_mul(vec3(1, 1, 1), 0.91339);
	return ;
}
