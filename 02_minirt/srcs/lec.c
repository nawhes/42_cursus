/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:43:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/30 23:01:25 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "io.h"
#include "vector.h"
#include "libft.h"
#include <stdlib.h>

#include "object.h"
#include "viewport.h"
#include "image.h"
#include <stdio.h>
#include "tools.h"

int main(int argc, char **argv)
{
	t_minirt	rt;
	rt.p_viewport = NULL;
	rt.p_object = NULL;
	rt.p_image = NULL;

	printf("argc : %d\n", argc);
	if (argc > 1)
		read_rt(*(argv + 1), &rt);
	else
		return (-1);

	image_render(&rt);

	t_output	output;
	output_init(&output, *(argv + 1), rt.p_image->content, ft_lstsize(rt.p_image));
	output_print(&output, output.info + 0, rt.p_image->content);
	//mlx_destroy_image(output.mlx, output.info->img);
	mlx_loop(output.mlx);
	return (0);
}
