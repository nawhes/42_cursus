/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 06:11:46 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "vector.h"
#include "object.h"

void		rt_light(t_minirt *rt)
{
	int		i;
	t_vec3	coord;
	double	ratio;
	t_vec3	rgb;

	i = 0;
	while (*(rt->line + i) == 'l' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &ratio))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &rgb))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
}
