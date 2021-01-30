/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 06:32:21 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "vector.h"
#include "object.h"

void		rt_rect(t_minirt *rt)
{
	int		i;
	double	locate[5];
	t_vec3	rgb;
	t_object	*p_object;
	int		texture;

	i = 0;
	while (*(rt->line + i) == 'r' || ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &locate[0]) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &locate[1]) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &locate[2]) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &locate[3]) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &locate[4]) || next(rt->line, &i))
		error_handle(-2, rt);
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
	p_object = object((void *)rect(locate[0], locate[1], locate[2], locate[3], locate[4], rgb), T_RECT, texture);
	ft_lstadd_back(&(rt->p_object), ft_lstnew((void *)p_object));
}
