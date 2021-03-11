/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 07:20:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/07 18:46:50 by sehpark          ###   ########.fr       */
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

static void	before_exit(t_minirt *rt)
{
	ft_lstclear(&(rt->p_viewport), free);
	ft_lstiter(rt->p_object, free_object_info);
	ft_lstclear(&(rt->p_object), free);
	ft_lstiter(rt->p_light, free_light_info);
	ft_lstclear(&(rt->p_light), free);
	ft_lstiter(rt->p_image, free_image_rgb);
	ft_lstclear(&(rt->p_image), free);
	free(rt->line);
	free(rt->p_viewport);
	free(rt->p_object);
	free(rt->p_image);
	return ;
}

void		error_handle(int handler, t_minirt *rt)
{
	if (handler != 0)
	{
		if (handler == -1)
			perror("File access");
		if (handler == -2)
			perror("Rt file property");
		if (handler == -3)
			perror("Memory allocate");
		if (handler == -4)
			perror("Output");
		if (handler == -5)
			perror("Arguments");
		before_exit(rt);
		exit(1);
	}
}
