/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 19:53:10 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*plane_node(t_plane pl, int material, double attr)
{
	t_plane		*p_pl;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_pl = plane(pl)))
		return (NULL);
	if (!(p_ob = object((void *)p_pl, OB_PLANE, material, attr)))
	{
		free(p_pl);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_pl);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

static void		get_plane(t_minirt *rt, t_plane *pl, int *i)
{
	if (atovec3(rt->line, i, &pl->coord))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &pl->normal))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &pl->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(pl->rgb, 0, 255))
		error_handle(-2, rt);
	pl->rgb = v_div(pl->rgb, 255);
	skip(rt->line, i);
}

void			rt_plane(t_minirt *rt)
{
	int			i;
	t_plane		pl;
	int			material;
	double		attr;
	t_list		*p_node;

	i = 0;
	skip2(rt->line, &i, 'p', 'l');
	get_plane(rt, &pl, &i);
	get_material_attr(rt, &i, &material, &attr);
	if (!(p_node = plane_node(pl, material, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
