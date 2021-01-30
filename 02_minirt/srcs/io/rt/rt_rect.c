/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 05:25:40 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "vector.h"
#include "object.h"

static t_list	*rect_node(t_rect rectangle, int texture)
{
	t_rect		*p_rect;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_rect = rect(rectangle)))
		return (NULL);
	if (!(p_ob = object((void *)p_rect, OB_RECT, texture)))
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

void		rt_rect(t_minirt *rt)
{
	int		i;
	t_rect	rectangle;
	t_list	*p_node;
	int		texture;

	i = 0;
	while (*(rt->line + i) == 'r' || ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &rectangle.x0) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.x1) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.y0) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.y1) || next(rt->line, &i))
		error_handle(-2, rt);
	if (check_atof_parameter(rt->line, &i, &rectangle.k))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &rectangle.rgb))
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

	if (!(p_node = rect_node(rectangle, texture)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
