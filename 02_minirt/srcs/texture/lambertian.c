/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/01 10:53:56 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		random_cosine_direction()
{
	double	r1 = random_double();
	double	r2 = random_double();
	double	z = sqrt(1 - r2);
	double	phi = 2 * PI * r1;
	double	x = cos(phi) * sqrt(r2);
	double	y = sin(phi) * sqrt(r2);
	return (vec3(x, y, z));
}

double		cosine_pdf(t_vec3 normal, t_vec3 wi)
{
//	t_onb	uvw;
//	uvw = onb_build_from_w(normal);
	double costheta;
	costheta = vec3_dot(vec3_unit_vector(wi), normal);
	if (costheta < 0)
		return (0);
	return (costheta / PI);
}

t_vec3		lambert_eval(t_hit_record rec, t_vec3 wi)
{
	t_vec3	normal = rec.normal;
	double	costheta = vec3_dot(wi, normal);
	return (vec3_mul(rec.albedo, costheta * 2.0));
}

void		lambertian(t_hit_record *rec, double *pdf)
{
	t_onb	uvw;
	t_vec3	wi;

	//sample
	uvw = onb_build_from_w(rec->normal);
	wi = onb_local(uvw, random_cosine_direction());
	//pdf
	*pdf = cosine_pdf(rec->normal, wi);
	rec->ray = ray(rec->p, wi);
	//eval
	rec->attenuation = vec3_mul(lambert_eval(*rec, wi), *pdf);
	return ;
}
