/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/06 05:12:47 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*cylinder_node(t_cylinder cy, int texture, double attr)
{
	t_cylinder	*p_cy;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_cy = cylinder(cy)))
		return (NULL);
	if (!(p_ob = object((void *)p_cy, OB_CYLINDER, texture, attr)))
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

void			rt_cylinder(t_minirt *rt)
{
	int			i;
	t_cylinder	cy;
	int			texture;
	double		attr;
	t_list		*p_node;

	i = 0;
	while (*(rt->line + i) == 'c' || *(rt->line + i) == 'y' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &cy.coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &cy.normal))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &cy.radius))
		error_handle(-2, rt);
	cy.radius = cy.radius / 2;
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &cy.height))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &cy.rgb))
		error_handle(-2, rt);
	cy.rgb = v_div(cy.rgb, 255);
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

	if (!(p_node = cylinder_node(cy, texture, attr)))
	error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
