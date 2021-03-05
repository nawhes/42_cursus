/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 21:32:55 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:34:21 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray			ray(t_vec3 orig, t_vec3 dir)
{
	t_ray		ret;

	ret.orig = orig;
	ret.dir = dir;
	return (ret);
}

t_vec3			ray_at(t_ray a, double t)
{
	t_vec3		ret;

	ret.x = a.orig.x + t * a.dir.x;
	ret.y = a.orig.y + t * a.dir.y;
	ret.z = a.orig.z + t * a.dir.z;
	return (ret);
}
