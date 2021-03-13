/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ob_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:58:21 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 20:43:15 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		get_ob_info(t_minirt *rt, int *i, t_ob_info *ob_info)
{
	if (check_atoi_parameter(rt->line, i, &(ob_info->material)))
		error_handle(-2, rt);
	if (check_range_int(ob_info->material, 1, 6))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, &(ob_info->attr)))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atoi_parameter(rt->line, i, &(ob_info->texture)))
		error_handle(-2, rt);
	if (check_range_int(ob_info->texture, 0, 3))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (*(rt->line + *i) != '\0')
		error_handle(-2, rt);
}
