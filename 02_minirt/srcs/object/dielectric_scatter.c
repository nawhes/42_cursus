/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric_scatter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:23:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 05:46:19 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "viewport.h"
#include "vector.h"
#include "tools.h"

double		reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * pow((1.0 - cosine), 5));
}

int			dielectric_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered)
{
	double	refraction_ratio;
	t_vec3	unit_direction;
	double	ir;
	double	cos_theta;
	double	sin_theta;
	t_vec3	direction;


	ir = 1.5;
	//*attenuation = rec->rgb;
	*attenuation = vec3(1, 1, 1);
	unit_direction = vec3_unit_vector(r_in->dir);
	refraction_ratio = rec->front_face ? (1.0 / ir) : ir;
	cos_theta = fmin(vec3_dot(vec3_mul(unit_direction, -1), rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	if (refraction_ratio * sin_theta > 1.0 || reflectance(cos_theta, refraction_ratio) > random_double())
		direction = reflect(unit_direction, rec->normal);
	else
		direction = refract(unit_direction, rec->normal, refraction_ratio);

	*scattered = ray(rec->p, direction);
	return (1);
}
