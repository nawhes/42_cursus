/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atovec3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:42:03 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 18:11:16 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			atovec3(char *line, int *i, t_vec3 *target)
{
	double	x;
	double	y;
	double	z;

	if (check_atof_parameter(line, i, &x))
		return (-1);
	skip1(line, i, ',');
	if (check_atof_parameter(line, i, &y))
		return (-1);
	skip1(line, i, ',');
	if (check_atof_parameter(line, i, &z))
		return (-1);
	*target = vec(x, y, z);
	return (0);
}
