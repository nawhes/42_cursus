/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal_scatter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/15 04:01:03 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "viewport.h"
#include "vector.h"

int			metal_scatter(t_ray *r_in, t_hit_record *rec, t_vec3 *attenuation, t_ray *scattered)
{
	t_vec3	reflected;

	reflected = reflect(vec3_unit_vector(r_in->dir), rec->normal);
	*scattered = ray_construct(rec->p, reflected);
	*attenuation = rec->rgb;
	return (vec3_dot(scattered->dir, rec->normal) > 0);
}
