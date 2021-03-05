/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_pdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 05:22:17 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/06 05:26:22 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double		light_pdf(t_object *p_ob, t_ray r)
{
	t_sphere		*sp = (t_sphere *)p_ob->info;
	t_record	rec;
	t_brdf		brdf;
	rec = record();
	if (!p_ob->hit(*p_ob, r, &rec, &brdf))
	{
		return (0);
	}
	double	radius = sp->radius;
	double	distance = v_length_sq(v_sub_v(sp->coord, r.orig));
	double	cos_theta_max = sqrt(1.0 - radius * radius / distance);
	double	solid_angle = 2.0 * M_PI * (1.0 - cos_theta_max);
	return (1.0 / solid_angle);
}
