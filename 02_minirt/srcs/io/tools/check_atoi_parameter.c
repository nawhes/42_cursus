/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_atoi_parameter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:42:03 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 21:21:02 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			check_atoi_parameter(char *param, int *i, int *target)
{
	if (!ft_isdigit(*(param + *i)) && *(param + *i) != '-')
		return (-1);
	*target = ft_atoi(param + *i);
	while (ft_isdigit(*(param + *i)))
		(*i)++;
	return (0);
}
