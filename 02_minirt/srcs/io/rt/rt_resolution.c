/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_resolution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:18:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 21:23:18 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "tools.h"
#include "rt.h"
#include "image.h"
#include "libft.h"

void		rt_resolution(t_minirt *rt)
{
	t_image	*p_image;
	int		width;
	int		height;
	int		i;

	i = 0;
	while (*(rt->line + i) == 'R' || ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &width))
		error_handle(-2, rt);
	//have to check MAX_WIDTH
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (check_atoi_parameter(rt->line, &i, &height))
		error_handle(-2, rt);
	while (ft_isspace(*(rt->line + i)))
		i++;
	if (*(rt->line + i) != '\0')
		error_handle(-2, rt);
	p_image = image_init(width, height);
	ft_lstadd_back(&(rt->p_image), ft_lstnew((void *)p_image));
}
