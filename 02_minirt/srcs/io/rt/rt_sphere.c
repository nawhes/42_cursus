/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 20:49:34 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*sphere_node(t_sphere sp, t_ob_info ob_info)
{
	t_sphere	*p_sp;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_sp = sphere(sp)))
		return (NULL);
	if (!(p_ob = object((void *)p_sp, OB_SPHERE, ob_info)))
	{
		free(p_sp);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_sp);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

static void		get_sphere(t_minirt *rt, t_sphere *sp, int *i)
{
	if (atovec3(rt->line, i, &sp->coord))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &sp->radius))
		error_handle(-2, rt);
	if (check_range_double(sp->radius, 0.001, INFINITY))
		error_handle(-2, rt);
	sp->radius = sp->radius / 2;
	skip(rt->line, i);
	if (atovec3(rt->line, i, &sp->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(sp->rgb, 0, 255))
		error_handle(-2, rt);
	sp->rgb = v_div(sp->rgb, 255);
	skip(rt->line, i);
}

void			rt_sphere(t_minirt *rt)
{
	int			i;
	t_sphere	sp;
	t_ob_info	ob_info;
	t_list		*p_node;

	i = 0;
	skip2(rt->line, &i, 's', 'p');
	get_sphere(rt, &sp, &i);
	get_ob_info(rt, &i, &ob_info);
	if (!(p_node = sphere_node(sp, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
