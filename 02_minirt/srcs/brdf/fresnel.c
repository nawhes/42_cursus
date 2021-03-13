/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fresnel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 21:08:17 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 21:51:30 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		fresnel_double(double costheta, double f0)
{
	double	x;

	x = pow(1.0 - costheta, 5.0);
	return (fmax(0.0, fmin(1.0, f0 + (1.0 - f0) * x)));
}

t_vec3		fresnel_vec3(double costheta, t_vec3 f0)
{
	t_vec3	fresnel;

	fresnel.x = fresnel_double(costheta, f0.x);
	fresnel.y = fresnel_double(costheta, f0.y);
	fresnel.z = fresnel_double(costheta, f0.z);
	return (fresnel);
}
