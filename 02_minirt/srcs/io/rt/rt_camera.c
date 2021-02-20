/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/18 04:47:40 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*viewport_node(t_viewport vp)
{
	t_viewport	*p_vp;
	t_list		*p_node;
	
	if (!(p_vp = viewport(vp)))
		return (NULL);
	if (!(p_node = ft_lstnew((void *)p_vp)))
	{
		free(p_vp);
		return (NULL);
	}
	return (p_node);
}

void		rt_camera(t_minirt *rt)
{
	int		i;
	t_viewport	vp;
	t_list	*p_node;

	i = 0;
	while (*(rt->line + i) == 'c' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &vp.lookfrom))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &vp.lookat))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &vp.vfov))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	vp.aspect_ratio = (double)rt->r_x / (double)rt->r_y;
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	if (!(p_node = viewport_node(vp)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_viewport), p_node);
}
