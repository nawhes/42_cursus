/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 19:52:21 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*square_node(t_square sq, int material, double attr)
{
	t_square	*p_sq;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_sq = square(sq)))
		return (NULL);
	if (!(p_ob = object((void *)p_sq, OB_SQUARE, material, attr)))
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
	if (atovec3(rt->line, i, &sq->normal))
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

void			rt_square(t_minirt *rt)
{
	int			i;
	t_square	sq;
	int			material;
	double		attr;
	t_list		*p_node;

	i = 0;
	skip2(rt->line, &i, 's', 'q');
	get_square(rt, &sq, &i);
	get_material_attr(rt, &i, &material, &attr);
	if (!(p_node = square_node(sq, material, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
