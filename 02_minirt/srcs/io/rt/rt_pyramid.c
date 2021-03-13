/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pyramid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/14 02:59:36 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*triangle_node(t_triangle tri, t_ob_info ob_info)
{
	t_triangle	*p_tri;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_tri = triangle(tri)))
		return (NULL);
	if (!(p_ob = object((void *)p_tri, OB_TRIANGLE, ob_info)))
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

static t_list	*square_node(t_square sq, t_ob_info ob_info)
{
	t_square	*p_sq;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_sq = square(sq)))
		return (NULL);
	if (!(p_ob = object((void *)p_sq, OB_SQUARE, ob_info)))
	{
		free(p_sq);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_sq);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

static void		get_pyramid(t_minirt *rt, t_pyramid *py, int *i)
{
	if (atovec3(rt->line, i, &py->coord))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &py->side_size))
		error_handle(-2, rt);
	if (check_range_double(py->side_size, 0.001, INFINITY))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &py->height))
		error_handle(-2, rt);
	if (check_range_double(py->side_size, 0.001, INFINITY))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &py->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(py->rgb, 0, 255))
		error_handle(-2, rt);
	py->rgb = v_div(py->rgb, 255);
	skip(rt->line, i);
}

static void		rt_pyramid2(t_minirt *rt,
		t_square sq,
		double height,
		t_ob_info ob_info)
{
	t_triangle	tri;
	t_list		*p_node;

	tri.rgb = sq.rgb;
	tri.point1 = vec(sq.coord.x, sq.coord.y + height, sq.coord.z);
	tri.point2 = v_add_v(sq.coord, vec(sq.side_size / 2, 0, sq.side_size / 2));
	tri.point3 = v_add_v(sq.coord, vec(-sq.side_size / 2, 0, sq.side_size / 2));
	if (!(p_node = triangle_node(tri, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	tri.point2.z -= sq.side_size;
	tri.point3.z -= sq.side_size;
	if (!(p_node = triangle_node(tri, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	tri.point2 = v_add_v(sq.coord, vec(sq.side_size / 2, 0, sq.side_size / 2));
	tri.point3 = v_add_v(sq.coord, vec(sq.side_size / 2, 0, -sq.side_size / 2));
	if (!(p_node = triangle_node(tri, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	tri.point2.x -= sq.side_size;
	tri.point3.x -= sq.side_size;
	if (!(p_node = triangle_node(tri, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}

void			rt_pyramid(t_minirt *rt)
{
	int			i;
	t_pyramid	py;
	t_square	sq;
	t_ob_info	ob_info;
	t_list		*p_node;

	i = 0;
	skip2(rt->line, &i, 'p', 'y');
	get_pyramid(rt, &py, &i);
	get_ob_info(rt, &i, &ob_info);
	sq.coord = py.coord;
	sq.rgb = py.rgb;
	sq.side_size = py.side_size;
	sq.normal = vec(0, 1, 0);
	if (!(p_node = square_node(sq, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	rt_pyramid2(rt, sq, py.height, ob_info);
}
