/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 20:44:08 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*cylinder_node(t_cylinder cy, t_ob_info ob_info)
{
	t_cylinder	*p_cy;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_cy = cylinder(cy)))
		return (NULL);
	if (!(p_ob = object((void *)p_cy, OB_CYLINDER, ob_info)))
	{
		free(p_cy);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_cy);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

static void		get_cylinder(t_minirt *rt, t_cylinder *cy, int *i)
{
	if (atovec3(rt->line, i, &cy->coord))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &cy->normal))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &cy->radius))
		error_handle(-2, rt);
	if (check_range_double(cy->radius, 0.001, INFINITY))
		error_handle(-2, rt);
	cy->radius = cy->radius / 2.0;
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &cy->height))
		error_handle(-2, rt);
	if (check_range_double(cy->height, 0.001, INFINITY))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &cy->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(cy->rgb, 0, 255))
		error_handle(-2, rt);
	cy->rgb = v_div(cy->rgb, 255);
	skip(rt->line, i);
}

void			rt_cylinder(t_minirt *rt)
{
	int			i;
	t_cylinder	cy;
	t_ob_info	ob_info;
	t_list		*p_node;

	i = 0;
	skip2(rt->line, &i, 'c', 'y');
	get_cylinder(rt, &cy, &i);
	get_ob_info(rt, &i, &ob_info);
	if (!(p_node = cylinder_node(cy, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
