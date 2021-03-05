/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/05 13:39:04 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*rect_node(t_rect rectangle, int texture, double attr)
{
	t_rect		*p_rectangle;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_rectangle = rect(rectangle)))
		return (NULL);
	if (!(p_ob = object((void *)p_rectangle, OB_RECT, texture, attr)))
	{
		free(p_rectangle);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_rectangle);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

void		rt_rect(t_minirt *rt)
{
	int			i;
	t_rect		rectangle;
	int			texture;
	double		attr;
	t_list		*p_node;

	i = 0;
	while (*(rt->line + i) == 'r' || *(rt->line + i) == 't' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &rectangle.coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &rectangle.normal))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &rectangle.width))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &rectangle.height))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &rectangle.rgb))
		error_handle(-2, rt);
	rectangle.rgb = v_div(rectangle.rgb, 255);
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

	if (!(p_node = rect_node(rectangle, texture, attr)))
	error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
