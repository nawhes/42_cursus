/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microfacet_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 20:21:30 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 21:08:33 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		ggx2(double roughness, double costheta)
{
	double	a2;
	double	exp;

	a2 = roughness * roughness;
	exp = (a2 - 1.0) * costheta * costheta + 1.0;
	return (a2 / (M_PI * exp * exp));
}

double		v1(double roughness, double ndotx)
{
	double	a2;

	a2 = roughness * roughness;
	return (1.0 / (ndotx + sqrt(a2 + (1.0 - a2) * ndotx * ndotx)));
}

double		v(double roughness, double ndotwi, double ndotwo)
{
	return (v1(roughness, ndotwi) * v1(roughness, ndotwo));
}

double		g1(double roughness, double ndotx)
{
	double	a2;

	a2 = roughness * roughness;
	return (2.0 * ndotx / (ndotx + sqrt(a2 + (1.0 - a2) * ndotx * ndotx)));
}
