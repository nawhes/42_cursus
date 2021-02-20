/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/21 05:32:18 by sehpark          ###   ########.fr       */
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

void		lambertian(t_hit_record *rec, t_vec3 dir)
{
	t_onb	uvw;

	if (random_double() > 0.5)
	{
		uvw = onb_build_from_w(rec->normal);
		dir = onb_local(uvw, random_cosine_direction());
	}
	rec->ray = ray(rec->p, dir);
	rec->attenuation = rec->albedo;
	return ;
}
