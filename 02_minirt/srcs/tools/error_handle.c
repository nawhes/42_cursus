/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 07:20:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/13 14:04:42 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_object_info(void *ob)
{
	t_object	*tmp;

	tmp = (t_object *)ob;
	free(tmp->info);
	return ;
}

static void	free_light_info(void *ob)
{
	t_object	*tmp;

	tmp = (t_object *)ob;
	free(tmp->info);
	return ;
}

static void	free_image_rgb(void *img)
{
	t_image	*tmp;

	tmp = (t_image *)img;
	free(tmp->rgba);
	return ;
}

void		before_exit(t_minirt *rt)
{
	if (rt->p_object)
		ft_lstiter(rt->p_object, free_object_info);
	if (rt->p_light)
		ft_lstiter(rt->p_light, free_light_info);
	if (rt->p_image)
		ft_lstiter(rt->p_image, free_image_rgb);
	ft_lstclear(&(rt->p_viewport), free);
	ft_lstclear(&(rt->p_object), free);
	ft_lstclear(&(rt->p_light), free);
	ft_lstclear(&(rt->p_image), free);
	free(rt->p_viewport);
	free(rt->p_object);
	free(rt->p_image);
	free(rt->p_mlx);
	free(rt->line);
	return ;
}

void		error_handle(int handler, t_minirt *rt)
{
	before_exit(rt);
	if (handler != 0)
	{
		if (handler == -1)
			perror("Error\nFile access");
		if (handler == -2)
			perror("Error\n(Logical) Rt file property Error");
		if (handler == -3)
			perror("Error\nMemory allocate");
		if (handler == -4)
			perror("Error\nMlx");
		if (handler == -5)
			perror("Error\n(Logical) Argument Error");
		exit(1);
	}
	exit(0);
}
