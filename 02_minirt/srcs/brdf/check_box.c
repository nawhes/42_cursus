/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 04:25:09 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:38:32 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		check_box(t_brdf *brdf)
{
	double sines;

	sines = sin(10 * brdf->point.x);
	sines *= sin(10 * brdf->point.y);
	sines *= sin(10 * brdf->point.z);
	if (sines < 0)
		brdf->albedo = vec(0.2, 0.3, 0.1);
	else
		brdf->albedo = vec(0.9, 0.9, 0.9);
	lambertian(brdf);
	return ;
}
