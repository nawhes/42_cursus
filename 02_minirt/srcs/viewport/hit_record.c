/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:09:58 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/21 00:27:59 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			hit_record_set_face_normal
(t_hit_record *this, t_ray r, t_vec3 *outward_normal)
{
	this->front_face = vec3_dot(r.dir, *outward_normal) < 0;
	if (this->front_face)
		this->normal = *outward_normal;
	else
		this->normal = vec3_mul(*outward_normal, -1.0);
}

t_hit_record		hit_record()
{
	t_hit_record	this;

	this.t_min = 0.001;
	this.t_max = INFINITY;
	this.albedo = vec3(0, 0, 0);
	this.emitted = vec3(0, 0, 0);
	this.attenuation = vec3(0, 0, 0);
	this.set_face_normal = hit_record_set_face_normal;
	return (this);
}
