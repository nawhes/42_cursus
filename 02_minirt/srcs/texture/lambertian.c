/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/28 06:08:12 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3		random_cosine_direction()
{
	double	r1 = random_double();
	double	r2 = random_double();
	double	z = sqrt(1 - r2);
	double	phi = 2 * PI * r1;
	double	x = cos(phi) * sqrt(r2);
	double	y = sin(phi) * sqrt(r2);
	return (vec3(x, y, z));
}

static double	cosine_pdf(t_vec3 normal, t_vec3 dir)
{
	t_onb	uvw;
	uvw = onb_build_from_w(normal);
	double cosine;
	cosine = vec3_dot(vec3_unit_vector(dir), uvw.w);
	if (cosine < 0)
		return (0);
	return (cosine / PI);
}

void		lambertian(t_hit_record *rec, t_vec3 dir, double *texture_pdf)
{
	t_onb	uvw;

	//sample
	if (random_double() > 0.5)
	{
		uvw = onb_build_from_w(rec->normal);
		dir = onb_local(uvw, random_cosine_direction());
	}
	//eval
	*texture_pdf = cosine_pdf(rec->normal, dir);
	rec->ray = ray(rec->p, dir);
	//eval
	rec->attenuation = rec->albedo;
//	rec->attenuation = vec3_mul(rec->albedo, *texture_pdf * 2);
	return ;
}
