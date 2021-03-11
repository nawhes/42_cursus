/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:08:45 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/07 20:46:50 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_image			*image(t_minirt *rt)
{
	t_image		*image;

	if (!(image = malloc(sizeof(t_image))))
		return (NULL);
	if (!(image->rgba = malloc(sizeof(int) * rt->pixel)))
		return (NULL);
	ft_bzero(image->rgba, sizeof(int) * rt->pixel);
	return (image);
}
