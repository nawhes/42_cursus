/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ambientlight.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 18:10:18 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_ambientlight(t_minirt *rt)
{
	rt->ambient_rgb = v_div(rt->ambient_rgb, 255);
	rt->ambient_rgb = v_mul(rt->ambient_rgb, rt->ambient_ratio);
}

void		rt_ambientlight(t_minirt *rt)
{
	int		i;

	i = 0;
	skip1(rt->line, &i, 'A');
	if (check_atof_parameter(rt->line, &i, &rt->ambient_ratio))
		error_handle(-2, rt);
	if (check_range_double(rt->ambient_ratio, 0, 1))
		error_handle(-2, rt);
	skip(rt->line, &i);
	if (atovec3(rt->line, &i, &(rt->ambient_rgb)))
		error_handle(-2, rt);
	if (check_range_vec3(rt->ambient_rgb, 0, 255))
		error_handle(-2, rt);
	skip(rt->line, &i);
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	set_ambientlight(rt);
}
