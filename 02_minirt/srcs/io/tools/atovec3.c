/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atovec3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:42:03 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:05:46 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			atovec3(char *line, int *i, t_vec3 *target)
{
	double	x;
	double	y;
	double	z;

	if (check_atof_parameter(line, i, &x) || next(line, i))
		return (-1);
	if (check_atof_parameter(line, i, &y) || next(line, i))
		return (-1);
	if (check_atof_parameter(line, i, &z))
		return (-1);
	*target = vec(x, y, z);
	// have to check_range
	return (0);
}
