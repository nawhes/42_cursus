/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:00:48 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*sphere_node(t_sphere sp, int texture, double attr)
{
	t_sphere	*p_sp;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_sp = sphere(sp)))
		return (NULL);
	if (!(p_ob = object((void *)p_sp, OB_SPHERE, texture, attr)))
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

void		rt_light(t_minirt *rt)
{
	int			i;
	t_sphere	sp;
	double		attr;
	t_list		*p_node;

	i = 0;
	while (*(rt->line + i) == 'l' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &sp.coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &sp.diameter))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &sp.rgb))
		error_handle(-2, rt);
	sp.rgb = v_div(sp.rgb, 255);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &attr))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	
//	if (!(p_node = sphere_node(sp, DIFFUSE_LIGHT, attr)))
//		error_handle(-3, rt);
//	ft_lstadd_back(&(rt->p_object), p_node);
	if (!(p_node = sphere_node(sp, DIFFUSE_LIGHT, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_light), p_node);
}
