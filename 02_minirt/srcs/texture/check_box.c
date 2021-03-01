/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 04:25:09 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/01 01:04:07 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_box(t_hit_record *rec, double *texture_pdf)
{
	double sines;
	sines = sin(10 * rec->p.x) * sin(10 * rec->p.y) * sin(10 * rec->p.z);
	if (sines < 0)
		rec->albedo = vec3(0.2, 0.3, 0.1);
	else
		rec->albedo = vec3(0.9, 0.9, 0.9);
	lambertian(rec, texture_pdf);
	return ;
}
