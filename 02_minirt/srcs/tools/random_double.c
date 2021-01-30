/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:42:22 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/09 06:08:57 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

double		random_double(void)
{
	return (rand() / (RAND_MAX + 1.0));
}

double		random_double_range(double min, double max)
{
	return (min + (max - min) * random_double());
}
