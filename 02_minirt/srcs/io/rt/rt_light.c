/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/04/07 21:56:47 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*sphere_node(t_sphere sp, double attr)
{
	t_sphere	*p_sp;
	t_object	*p_ob;
	t_list		*p_node;
	t_ob_info	ob_info;

	if (!(p_sp = sphere(sp)))
		return (NULL);
	ob_info.material = DIFFUSE_LIGHT;
	ob_info.attr = attr;
	ob_info.texture = TX_NONE;
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

void			rt_light(t_minirt *rt)
{
	int			i;
	t_sphere	sp;
	double		attr;
	t_list		*p_node;

	i = 0;
	skip1(rt->line, &i, 'l');
	get_sphere(rt, &sp, &i);
	if (check_atof_parameter(rt->line, &i, &attr))
		error_handle(-2, rt);
	sp.rgb = v_mul(sp.rgb, attr);
	skip(rt->line, &i);
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	if (!(p_node = sphere_node(sp, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_light), p_node);
	if (!(p_node = sphere_node(sp, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
