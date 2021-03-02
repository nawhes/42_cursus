/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:43:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 08:00:02 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "vector.h"
#include "minirt.h"

static t_minirt	minirt()
{
	t_minirt	this;

	this.p_viewport = NULL;
	this.p_object = NULL;
	this.p_light = NULL;
	this.p_image = NULL;
	return (this);
}

int main(int argc, char **argv)
{
	t_minirt	rt;
	rt = minirt();

	printf("argc : %d\n", argc);
	if (argc > 1)
		read_rt(*(argv + 1), &rt);
	else
	{
		return (0);
	}

	image_render(&rt);

	t_output	*p_output;
	if (!(p_output = output(*(argv + 1), &rt)))
		error_handle(-4, &rt);
	output_print(p_output, &rt);
	//mlx_destroy_image(output.mlx, output.info->img);
	mlx_loop(p_output->mlx);
	return (0);
}
