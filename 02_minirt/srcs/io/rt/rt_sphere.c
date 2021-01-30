/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 06:17:35 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "vector.h"
#include "object.h"

static t_list	*sphere_node(t_sphere sp, int texture)
{
	t_sphere	*p_sp;
	t_object	*p_ob;
	t_list		*p_node;

	if (!(p_sp = sphere(sp)))
		return (NULL);
	if (!(p_ob = object((void *)p_sp, OB_SPHERE, texture)))
	{
		free(p_sp);
		return (NULL);
	}
	if (!(p_node = ft_lstnew((void *)p_ob)))
	{
		free(p_sp);
		free(p_ob);
		return (NULL);
	}
	return (p_node);
}

void		rt_sphere(t_minirt *rt)
{
	int			i;
	t_sphere	sp;
	int			texture;
	t_list		*p_node;

	i = 0;
	while (*(rt->line + i) == 's' || *(rt->line + i) == 'p' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &sp.coord))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &sp.diameter))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &sp.rgb))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &texture))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);

	if (!(p_node = sphere_node(sp, texture)))
		error_handle(-3, rt);
	ft_lstadd_back(&(rt->p_object), p_node);
}
