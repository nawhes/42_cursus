/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambertian_scatter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/11 04:17:56 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "viewport.h"
#include "vector.h"

int			lambertian_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	scatter_direction;

	r_in->dir = r_in->dir;
	scatter_direction = vec3_add(rec->normal, vec3_random_unit_vector());
	if (vec3_near_zero(scatter_direction))
		scatter_direction = rec->normal;
	*scattered = ray_construct(rec->p, scatter_direction);
	*attenuation = rec->rgb;
	return (1);
}
