/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:16:22 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/18 06:01:24 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
** Grayscale = 0.299R + 0.587G + 0.114B
** https://en.wikipedia.org/wiki/Grayscale
** https://www.geeksforgeeks.org/image-processing-in-java-set-3-colored-image
** -to-greyscale-image-conversion/?ref=lbp
*/

static void		grayscale_filter(t_vec3 *rgb)
{
	rgb->x = rgb->x * 0.299;
	rgb->y = rgb->y * 0.587;
	rgb->z = rgb->z * 0.114;
}

static void		invert_filter(t_vec3 *rgb)
{
	rgb->x = 1.0 - rgb->x;
	rgb->y = 1.0 - rgb->y;
	rgb->z = 1.0 - rgb->z;
}

static void		sepia_filter(t_vec3 *rgb)
{
	rgb->x = 0.393 * rgb->x + 0.769 * rgb->y + 0.189 * rgb->z;
	rgb->y = 0.349 * rgb->x + 0.686 * rgb->y + 0.168 * rgb->z;
	rgb->z = 0.272 * rgb->x + 0.534 * rgb->y + 0.131 * rgb->z;
}

static void		rgb_filter(t_vec3 *rgb, int i, int r_x, int r_y)
{
	if (i / r_x < r_y / 2)
	{
		if (i % r_x < r_x / 2)
		{
			rgb->y = 0;
			rgb->z = 0;
		}
		else
		{
			rgb->x = 0;
			rgb->z = 0;
		}
	}
	else
	{
		if (i % r_x < r_x / 2)
		{
			rgb->x = 0;
			rgb->y = 0;
		}
	}
}

void			image_filter(t_vec3 *rgb, int i, int r_x, int r_y)
{
	if (SEPIA_FILTER)
		sepia_filter(rgb);
	else if (GRAYSCALE_FILTER)
		grayscale_filter(rgb);
	else if (INVERT_FILTER)
		invert_filter(rgb);
	else if (RGB_FILTER)
		rgb_filter(rgb, i, r_x, r_y);
}
