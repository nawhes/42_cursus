/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/05 13:39:33 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*square_node(t_square sq, int texture, double attr)
{
	t_square	*p_sq;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_sq = square(sq)))
		return (NULL);
	if (!(p_ob = object((void *)p_sq, OB_SQUARE, texture, attr)))
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

void		rt_square(t_minirt *rt)
{
	int			i;
	t_square	sq;
	int			texture;
	double		attr;
	t_list		*p_node;

	i = 0;
	while (*(rt->line + i) == 's' || *(rt->line + i) == 'q' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &sq.coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &sq.normal))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &sq.side_size))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &sq.rgb))
		error_handle(-2, rt);
	sq.rgb = v_div(sq.rgb, 255);
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

	if (!(p_node = square_node(sq, texture, attr)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
