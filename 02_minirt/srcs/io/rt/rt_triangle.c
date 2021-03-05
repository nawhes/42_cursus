/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/05 14:32:56 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*triangle_node(t_triangle tri, int texture, double attr)
{
	t_triangle	*p_tri;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_tri = triangle(tri)))
		return (NULL);
	if (!(p_ob = object((void *)p_tri, OB_TRIANGLE, texture, attr)))
	{
		free(p_tri);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_tri);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

void		rt_triangle(t_minirt *rt)
{
	int			i;
	t_triangle	tri;
	int			texture;
	double		attr;
	t_list		*p_node;

	i = 0;
	while (*(rt->line + i) == 't' || *(rt->line + i) == 'r' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &tri.point1))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &tri.point2))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &tri.point3))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &tri.rgb))
		error_handle(-2, rt);
	tri.rgb = v_div(tri.rgb, 255);
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

	if (!(p_node = triangle_node(tri, texture, attr)))
	error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
