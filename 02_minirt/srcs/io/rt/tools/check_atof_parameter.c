/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_atof_parameter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:42:03 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 21:21:22 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			check_atof_parameter(char *param, int *i, double *target)
{
	if (!ft_isdigit(*(param + *i)) && *(param + *i) != '-')
		return (-1);
	*target = ft_atof(param + *i);
	while (ft_isdigit(*(param + *i)) || *(param + *i) == '.' || 
			*(param + *i) == '-')
		(*i)++;
	return (0);
}
