/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_material_attr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 19:58:21 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 19:58:30 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		get_material_attr(t_minirt *rt, int *i, int *material, double *attr)
{
	if (check_atoi_parameter(rt->line, i, material))
		error_handle(-2, rt);
	if (check_range_int(*material, 1, 7))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (check_atof_parameter(rt->line, i, attr))
		error_handle(-2, rt);
	skip(rt->line, i);
	if (*(rt->line + *i) != '\0')
		error_handle(-2, rt);
}
