/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 03:43:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/14 01:08:11 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_minirt	minirt(void)
{
	t_minirt	this;

	this.p_viewport = NULL;
	this.p_object = NULL;
	this.p_light = NULL;
	this.p_image = NULL;
	this.p_mlx = NULL;
	this.r_x = 100;
	this.r_y = 100;
	this.pixel = 10000;
	this.line = NULL;
	this.ambient_rgb = vec3(0.1);
	return (this);
}

static int		parse_arg(
		int argc,
		char **argv,
		char **filename,
		int *flag_save)
{
	if (argc == 1)
		return (-1);
	*filename = *(argv + 1);
	if (argc > 2)
	{
		if (!ft_strncmp(*(argv + 2), "--save", 6))
		{
			*flag_save = 1;
			return (0);
		}
		return (-1);
	}
	*flag_save = 0;
	return (0);
}

int				main(int argc, char **argv)
{
	t_minirt	rt;
	int			flag_save;
	char		*filename;

	t_onb		uvw;
	uvw = onb_build_from_w(v_normalize(vec(0.3, 0, 1)));
	printf("(%f, %f, %f)\n", uvw.u.x, uvw.u.y, uvw.u.z);
	printf("(%f, %f, %f)\n", uvw.v.x, uvw.v.y, uvw.v.z);
	printf("(%f, %f, %f)\n", uvw.w.x, uvw.w.y, uvw.w.z);
	rt = minirt();
	if (parse_arg(argc, argv, &filename, &flag_save))
		error_handle(-5, &rt);
	read_rt(filename, &rt);
	if (rt.p_object == NULL || rt.p_viewport == NULL)
		error_handle(-2, &rt);
	if (flag_save)
	{
		render(&rt);
		export_bmp(filename, &rt);
		before_exit(&rt);
	}
	else
	{
		if (!(rt.p_mlx = mlx(&rt)))
			error_handle(-3, &rt);
		render(&rt);
		print_window(filename, &rt);
	}
	return (0);
}
