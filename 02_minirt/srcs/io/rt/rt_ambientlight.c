/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ambientlight.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:00:27 by sehpark          ###   ########.fr       */
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
	while (*(rt->line + i) == 'A' || ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &rt->ambient_ratio))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &(rt->ambient_rgb)))
		error_handle(-2, rt);
	set_ambientlight(rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
}
