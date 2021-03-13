/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:08:45 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 16:31:25 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_image			*image(t_minirt *rt)
{
	t_image		*image;

	if (!(image = malloc(sizeof(t_image))))
		error_handle(-3, rt);
	if (!(image->rgba = malloc(sizeof(int) * rt->pixel)))
		error_handle(-3, rt);
	ft_bzero(image->rgba, sizeof(int) * rt->pixel);
	return (image);
}
