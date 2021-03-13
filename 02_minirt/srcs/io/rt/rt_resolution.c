/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 18:05:58 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		rt_resolution(t_minirt *rt)
{
	int		i;

	i = 0;
	skip1(rt->line, &i, 'R');
	if (check_atoi_parameter(rt->line, &i, &rt->r_x))
		error_handle(-2, rt);
	if (check_range_int(rt->r_x, 0, INT32_MAX))
		error_handle(-2, rt);
	skip(rt->line, &i);
	if (check_atoi_parameter(rt->line, &i, &rt->r_y))
		error_handle(-2, rt);
	if (check_range_int(rt->r_y, 0, INT32_MAX))
		error_handle(-2, rt);
	rt->pixel = rt->r_x * rt->r_y;
	skip(rt->line, &i);
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
}
