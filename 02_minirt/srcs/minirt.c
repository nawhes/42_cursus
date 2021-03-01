/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:43:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/01 07:31:26 by sehpark          ###   ########.fr       */
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
		t_onb	uvw1, uvw2;
		uvw1 = onb_build_from_w(vec3(1, 0, 0));
		uvw2 = onb_build_from_v(vec3(1, 0, 0));
		t_vec3	dir1, dir2;
		dir1 = onb_local(uvw1, vec3(1, 1, 1));
		dir2 = onb_local(uvw2, vec3(1, 1, 1));
		printf("(%f, %f, %f)\n", uvw1.u.x, uvw1.u.y, uvw1.u.z);
		printf("(%f, %f, %f)\n", uvw1.v.x, uvw1.v.y, uvw1.v.z);
		printf("(%f, %f, %f)\n", uvw1.w.x, uvw1.w.y, uvw1.w.z);
		
		printf("--\n");
		printf("(%f, %f, %f)\n", uvw2.u.x, uvw2.u.y, uvw2.u.z);
		printf("(%f, %f, %f)\n", uvw2.v.x, uvw2.v.y, uvw2.v.z);
		printf("(%f, %f, %f)\n", uvw2.w.x, uvw2.w.y, uvw2.w.z);
		printf("--\n");
		printf("(%f, %f, %f)\n", dir1.x, dir1.y, dir1.z);
		printf("(%f, %f, %f)\n", dir2.x, dir2.y, dir2.z);

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
