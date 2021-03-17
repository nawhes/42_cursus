/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_pdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 05:22:17 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/18 05:54:39 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static double	get_illuminance(t_sphere *sp, t_ray r)
{
	double		radius;
	double		distance;
	double		costheta_max;
	double		solid_angle;

	radius = sp->radius;
	distance = v_length_sq(v_sub_v(sp->coord, r.orig));
	costheta_max = sqrt(1.0 - radius * radius / distance);
	solid_angle = 2.0 * M_PI * (1.0 - costheta_max);
	return (1.0 / solid_angle);
}

double			light_pdf(t_object *p_ob, t_ray r)
{
	t_sphere	*sp;

	sp = (t_sphere *)p_ob->info;
	return (get_illuminance(sp, r));
}
