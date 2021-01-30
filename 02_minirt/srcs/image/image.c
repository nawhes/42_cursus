/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:08:45 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/24 22:57:10 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "image.h"

t_image			*image_init(int width, int height)
{
	t_image		*image;
	int			i;

	if (!(image = malloc(sizeof(t_image))))
		return (NULL);
	image->width = width;
	image->height = height;
	if (!(image->rgb = (int **)malloc(sizeof(int *) * width)))
		return (NULL);
	i = 0;
	while (i < width)
	{
		if (!(*(image->rgb + i) = (int *)malloc(sizeof(int) * height)))
			return (NULL);
		ft_bzero(*(image->rgb + i), height);
		i++;
	}
	return (image);
}
