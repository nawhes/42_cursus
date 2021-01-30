/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 06:59:16 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "libft.h"
#include "viewport.h"

void		rt_camera(t_minirt *rt)
{
	int		i;
	t_vec3	lookfrom;
	t_vec3	lookat;
	double	vfov;
	double	aspect_ratio;
	t_viewport	*p_viewport;

	i = 0;
	while (*(rt->line + i) == 'c' || ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &lookfrom))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (atovec3(rt->line, &i, &lookat))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &vfov))
		error_handle(-2, rt);
	//have to check_range
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atof_parameter(rt->line, &i, &aspect_ratio))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	p_viewport = viewport_init(lookfrom, lookat, vfov, aspect_ratio);
	ft_lstadd_back(&(rt->p_viewport), ft_lstnew((void *)p_viewport));
}
