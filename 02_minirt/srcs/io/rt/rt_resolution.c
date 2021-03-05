/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 13:46:37 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*image_node(int width, int height)
{
	t_image	*p_img;
	t_list	*p_node;

	if (!(p_img = image(width, height)))
		return (NULL);
	if (!(p_node = ft_lstnew((void *)p_img)))
	{
		free(p_img);
		return (NULL);
	}
	return (p_node);
}

void		rt_resolution(t_minirt *rt)
{
	t_list	*p_node;
	int		i;

	i = 0;
	while (*(rt->line + i) == 'R' || ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &rt->r_x))
		error_handle(-2, rt);
	//have to check MAX_WIDTH
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &rt->r_y))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	if (!(p_node = image_node(rt->r_x, rt->r_y)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_image), p_node);
}
