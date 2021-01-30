/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 07:20:25 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/24 23:02:10 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"

static void	free_object_info(void *object)
{
	t_object	*tmp;

	tmp = (t_object *)object;
	free(tmp->info);
	return ;
}

static void	free_image_rgb(void *image)
{
	int		i;
	t_image	*tmp;

	i = 0;
	tmp = (t_image *)image;
	while (i < tmp->width)
	{
		free((tmp->rgb) + i);
		i++;
	}
	free(tmp->rgb);
	return ;
}

static void	before_exit(t_minirt *rt)
{
	ft_lstclear(&(rt->p_viewport), free);
	ft_lstiter(rt->p_object, free_object_info);
	ft_lstclear(&(rt->p_object), free);
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
			printf("Property Error !\n");
		before_exit(rt);
		exit(1);
	}
}
