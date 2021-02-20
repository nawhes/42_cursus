/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/18 04:52:57 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		metal(t_ray *r_in, t_hit_record *rec)
{
	t_vec3	dir;
	/*
	t_vec3	tmp;
	tmp = vec3_random_range(-rec->attr, rec->attr);
	tmp = vec3_add(tmp, r_in->dir);

	dir = reflect(vec3_unit_vector(tmp), rec->normal);
	*/
	dir = reflect(vec3_unit_vector(r_in->dir), rec->normal);
	rec->ray = ray(rec->p, dir);
	rec->attenuation = rec->albedo;
	return ;
}
