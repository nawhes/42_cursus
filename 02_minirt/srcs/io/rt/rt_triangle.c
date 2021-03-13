/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 19:55:29 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*triangle_node(t_triangle tri, int material, double attr)
{
	t_triangle	*p_tri;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_tri = triangle(tri)))
		return (NULL);
	if (!(p_ob = object((void *)p_tri, OB_TRIANGLE, material, attr)))
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

static void		get_triangle(t_minirt *rt, t_triangle *tri, int *i)
{
	if (atovec3(rt->line, i, &tri->point1))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &tri->point2))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &tri->point3))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &tri->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(tri->rgb, 0, 255))
		error_handle(-2, rt);
	tri->rgb = v_div(tri->rgb, 255);
	skip(rt->line, i);
}

void			rt_triangle(t_minirt *rt)
{
	int			i;
	t_triangle	tri;
	int			material;
	double		attr;
	t_list		*p_node;

	i = 0;
	skip2(rt->line, &i, 't', 'r');
	get_triangle(rt, &tri, &i);
	get_material_attr(rt, &i, &material, &attr);
	if (!(p_node = triangle_node(tri, material, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
