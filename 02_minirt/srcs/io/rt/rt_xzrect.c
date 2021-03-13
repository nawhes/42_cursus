/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_xzrect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 19:54:21 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*xzrect_node(t_xzrect rectangle, int texture, double attr)
{
	t_xzrect	*p_rect;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_rect = xzrect(rectangle)))
		return (NULL);
	if (!(p_ob = object((void *)p_rect, OB_XZRECT, texture, attr)))
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

static void		get_xzrect(t_minirt *rt, t_xzrect *rectangle, int *i)
{
	if (check_atof_parameter(rt->line, i, &rectangle->x0))
		error_handle(-2, rt);
	skip1(rt->line, i, ',');
	if (check_atof_parameter(rt->line, i, &rectangle->x1))
		error_handle(-2, rt);
	skip1(rt->line, i, ',');
	if (check_atof_parameter(rt->line, i, &rectangle->z0))
		error_handle(-2, rt);
	skip1(rt->line, i, ',');
	if (check_atof_parameter(rt->line, i, &rectangle->z1))
		error_handle(-2, rt);
	skip1(rt->line, i, ',');
	if (check_atof_parameter(rt->line, i, &rectangle->k))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &rectangle->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(rectangle->rgb, 0, 255))
		error_handle(-2, rt);
	rectangle->rgb = v_div(rectangle->rgb, 255);
	skip(rt->line, i);
}

void			rt_xzrect(t_minirt *rt)
{
	int			i;
	t_xzrect	rectangle;
	t_list		*p_node;
	int			material;
	double		attr;

	i = 0;
	skip2(rt->line, &i, 'x', 'y');
	get_xzrect(rt, &rectangle, &i);
	get_material_attr(rt, &i, &material, &attr);
	if (!(p_node = xzrect_node(rectangle, material, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
