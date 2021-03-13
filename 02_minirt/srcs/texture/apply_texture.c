/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:02:08 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/14 00:25:37 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		check_box(t_brdf *brdf)
{
	double		sines;

	sines = sin(3 * brdf->point.x);
	sines *= sin(3 * brdf->point.y);
	sines *= sin(3 * brdf->point.z);
	if (sines < 0)
		brdf->albedo = vec(0.1, 0.1, 0.1);
	else
		brdf->albedo = vec(0.9, 0.9, 0.9);
	return ;
}

static void		rainbow(t_brdf *brdf)
{
	double		costheta;

	costheta = v_dot(brdf->normal, vec(0, 1, 0));
	costheta += 1.0;
	if (costheta > 12.0 / 7.0)
		brdf->albedo = vec(1.0, 0.0, 0.0);
	else if (costheta > 10.0 / 7.0)
		brdf->albedo = vec(1.0, 0.498039, 0.0);
	else if (costheta > 8.0 / 7.0)
		brdf->albedo = vec(1.0, 1.0, 0.0);
	else if (costheta > 6.0 / 7.0)
		brdf->albedo = vec(0.0, 1.0, 0.0);
	else if (costheta > 4.0 / 7.0)
		brdf->albedo = vec(0.0, 0.0, 1.0);
	else if (costheta > 2.0 / 7.0)
		brdf->albedo = vec(0.294117, 0.0, 0.509803);
	else
		brdf->albedo = vec(0.560784, 0.0, 1);
	return ;
}

static void		wave(t_brdf *brdf)
{
	double		costheta;
	double		y;

	costheta = v_dot(brdf->normal, vec(0, 1, 0));
	costheta = acos(costheta);
	costheta = costheta * (180.0 / M_PI);
	y = sin(costheta);
	brdf->normal.y = y;
	brdf->normal = v_normalize(brdf->normal);
	return ;
}

void			apply_texture(int texture, t_brdf *brdf)
{
	if (texture == TX_CHECK_BOX)
		check_box(brdf);
	if (texture == TX_RAINBOW)
		rainbow(brdf);
	if (texture == TX_WAVE)
		wave(brdf);
}
