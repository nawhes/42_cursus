/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/14 02:21:27 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static void		get_square(t_minirt *rt, t_square *sq, int *i)
{
	if (atovec3(rt->line, i, &sq->coord))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &sq->side_size))
		error_handle(-2, rt);
	if (check_range_double(sq->side_size, 0.001, INFINITY))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (atovec3(rt->line, i, &sq->rgb))
		error_handle(-2, rt);
	if (check_range_vec3(sq->rgb, 0, 255))
		error_handle(-2, rt);
	sq->rgb = v_div(sq->rgb, 255);
	skip(rt->line, i);
}

static void		rt_cube2(t_minirt *rt, t_square sq, t_ob_info ob_info)
{
	t_square	new;
	t_list		*p_node;

	new = sq;
	new.normal = vec(1, 0, 0);
	new.coord = v_add_v(sq.coord, v_mul(new.normal, new.side_size / 2));
	if (!(p_node = square_node(new, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	new.coord = v_sub_v(sq.coord, v_mul(new.normal, new.side_size / 2));
	if (!(p_node = square_node(new, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	new.normal = vec(0, 0, 1);
	new.coord = v_sub_v(sq.coord, v_mul(new.normal, new.side_size / 2));
	if (!(p_node = square_node(new, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	new.coord = v_add_v(sq.coord, v_mul(new.normal, new.side_size / 2));
	if (!(p_node = square_node(new, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}

void			rt_cube(t_minirt *rt)
{
	int			i;
	t_square	sq;
	t_ob_info	ob_info;
	t_list		*p_node;
	t_square	new;

	i = 0;
	skip2(rt->line, &i, 'c', 'u');
	get_square(rt, &sq, &i);
	get_ob_info(rt, &i, &ob_info);
	new = sq;
	new.normal = vec(0, 1, 0);
	new.coord = v_sub_v(sq.coord, v_mul(new.normal, new.side_size / 2));
	if (!(p_node = square_node(new, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	new.coord = v_add_v(sq.coord, v_mul(new.normal, new.side_size / 2));
	if (!(p_node = square_node(new, ob_info)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
	rt_cube2(rt, sq, ob_info);
}
