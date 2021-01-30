/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 07:04:34 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "vector.h"
#include "object.h"

void		rt_sphere(t_minirt *rt)
{
	int		i;
	t_vec3	coord;
	double	diameter;
	t_vec3	rgb;
	t_object	*p_object;
	int		texture;

	i = 0;
	while (*(rt->line + i) == 's' || *(rt->line + i) == 'p' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &diameter))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &rgb))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &texture))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	p_object = object((void *)sphere(coord, diameter, rgb), T_SPHERE, texture);
	ft_lstadd_back(&(rt->p_object), ft_lstnew((void *)p_object));
}
