/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mirror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 03:44:34 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 09:36:17 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		mirror(t_brdf *brdf)
{
	brdf->wi = reflect(brdf->wo, brdf->normal);
	brdf->ray = ray(brdf->point, brdf->wi);
	brdf->attenuation = brdf->albedo;
	return ;
}
