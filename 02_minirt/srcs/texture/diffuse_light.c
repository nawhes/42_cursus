/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 04:17:00 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/18 04:52:30 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		diffuse_light(t_hit_record *rec)
{
	/*
	if (!rec->front_face)	
		rec->emitted = vec3_mul(rec->albedo, rec->attr);
	else
		rec->emitted = vec3(0, 0, 0);
	*/
	rec->emitted = vec3_mul(rec->albedo, rec->attr);
	return ;
}
