/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:57:03 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 19:59:29 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			check_range_int(int a, int min, int max)
{
	if (a < min || a > max)
		return (-1);
	return (0);
}

int			check_range_double(double a, double min, double max)
{
	if (a < min || a > max)
		return (-1);
	return (0);
}

int			check_range_vec3(t_vec3 a, double min, double max)
{
	if (a.x < min || a.x > max)
		return (-1);
	if (a.y < min || a.y > max)
		return (-1);
	if (a.z < min || a.z > max)
		return (-1);
	return (0);
}
