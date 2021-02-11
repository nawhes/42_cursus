/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_yzrect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/12 00:36:03 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "vector.h"
#include "object.h"

static t_list	*yzrect_node(t_yzrect rectangle, int texture)
{
	t_yzrect	*p_rect;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_rect = yzrect(rectangle)))
		return (NULL);
	if (!(p_ob = object((void *)p_rect, OB_YZRECT, texture)))
	{
		free(p_rect);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_rect);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

void		rt_yzrect(t_minirt *rt)
{
	int		i;
	t_yzrect	rectangle;
	t_list	*p_node;
	int		texture;

	i = 0;
	while (*(rt->line + i) == 'y' || *(rt->line + i) == 'z' || ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &rectangle.y0) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.y1) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.z0) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.z1) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.k))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &rectangle.rgb))
		error_handle(-2, rt);
	rectangle.rgb = vec3_div(rectangle.rgb, 255);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &texture))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);

	if (!(p_node = yzrect_node(rectangle, texture)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
