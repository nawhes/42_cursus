/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:09:58 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/21 02:07:57 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "vector.h"

void			hit_record_set_face_normal
(t_hit_record *this, t_ray *r, t_vec3 *outward_normal)
{
	this->front_face = vec3_dot(r->dir, *outward_normal) < 0;
	if (this->front_face)
		this->normal = *outward_normal;
	else
		this->normal = vec3_mul(*outward_normal, -1.0);
}

void			hit_record_init(t_hit_record *this)
{
	this->t_min = 0.001;
	this->t_max = INFINITY;
	this->set_face_normal = hit_record_set_face_normal;
}
