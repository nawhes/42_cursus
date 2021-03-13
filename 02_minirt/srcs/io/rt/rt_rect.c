/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 20:54:35 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*rect_node(t_rect rectangle, t_ob_info ob_info)
{
	t_rect		*p_rectangle;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_rectangle = rect(rectangle)))
		return (NULL);
	if (!(p_ob = object((void *)p_rectangle, OB_RECT, ob_info)))
	{
		free(p_rectangle);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_rectangle);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

static void		get_rect(t_minirt *rt, t_rect *rectangle, int *i)
{
	if (atovec3(rt->line, i, &rectangle->coord))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &rectangle->normal))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &rectangle->width))
		error_handle(-2, rt);
	if (check_range_double(rectangle->width, 0.001, INFINITY))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &rectangle->height))
		error_handle(-2, rt);
	if (check_range_double(rectangle->height, 0.001, INFINITY))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &rectangle->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(rectangle->rgb, 0, 255))
		error_handle(-2, rt);
	rectangle->rgb = v_div(rectangle->rgb, 255);
	skip(rt->line, i);
}

void			rt_rect(t_minirt *rt)
{
	int			i;
	t_rect		rectangle;
	t_ob_info	ob_info;
	t_list		*p_node;

	i = 0;
	skip2(rt->line, &i, 'r', 't');
	get_rect(rt, &rectangle, &i);
	get_ob_info(rt, &i, &ob_info);
	if (!(p_node = rect_node(rectangle, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
