/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 13:27:02 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*plane_node(t_plane pl, int texture, double attr)
{
	t_plane		*p_pl;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_pl = plane(pl)))
		return (NULL);
	if (!(p_ob = object((void *)p_pl, OB_PLANE, texture, attr)))
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

void		rt_plane(t_minirt *rt)
{
	int			i;
	t_plane		pl;
	int			texture;
	double		attr;
	t_list		*p_node;

	i = 0;
	while (*(rt->line + i) == 'p' || *(rt->line + i) == 'l' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &pl.coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &pl.normal))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &pl.rgb))
		error_handle(-2, rt);
	pl.rgb = v_div(pl.rgb, 255);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &texture))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &attr))
		error_handle(-2, rt);

	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);

	if (!(p_node = plane_node(pl, texture, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
