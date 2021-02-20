/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:42:22 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/21 05:32:21 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

double		random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double		random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}

int			random_int_range(int min, int max)
{
	return ((int)random_double_range(min, max + 1));
}
