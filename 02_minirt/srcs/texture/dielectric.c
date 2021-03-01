/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dielectric.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 00:23:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 04:20:22 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		reflectance(double cosine, double ref_idx)
{
	double	r0;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return (r0 + (1.0 - r0) * pow((1.0 - cosine), 5));
}

/*
t_ray		dielectric_sample(t_ray r, t_hit_record rec)
{
	double	refraction_ratio;
	t_vec3	unit_direction;
	double	ir;
	double	cos_theta;
	double	sin_theta;

	ir = 1.5;
	unit_direction = vec3_unit_vector(r_in.dir);
	refraction_ratio = rec->front_face ? (1.0 / ir) : ir;
	cos_theta = fmin(vec3_dot(vec3_mul(unit_direction, -1), rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	double	reflec = reflectance(cos_theta, refraction_ratio);
	if (refraction_ratio * sin_theta > 1.0 || 
			reflec > random_double())
		dir = reflect(unit_direction, rec->normal);
	else
		dir = refract(unit_direction, rec->normal, refraction_ratio);


}
*/

void		dielectric(t_ray r_in, t_hit_record *rec)
{
	t_vec3	dir;

	double	refraction_ratio;
	t_vec3	unit_direction;
	double	ir;
	double	cos_theta;
	double	sin_theta;

	ir = 1.5;
	unit_direction = vec3_unit_vector(r_in.dir);
	refraction_ratio = rec->front_face ? (1.0 / ir) : ir;
	cos_theta = fmin(vec3_dot(vec3_mul(unit_direction, -1), rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	double	reflec = reflectance(cos_theta, refraction_ratio);
	if (refraction_ratio * sin_theta > 1.0 || 
			reflec > random_double())
//	if (refraction_ratio * sin_theta > 1.0)
		dir = reflect(unit_direction, rec->normal);
	else
		dir = refract(unit_direction, rec->normal, refraction_ratio);

//	rec->attenuation = vec3_mul(vec3(1, 1, 1), 0.91339);
	rec->attenuation = vec3(1, 1, 1);
	rec->ray = ray(rec->p, dir);
	return ;
}
