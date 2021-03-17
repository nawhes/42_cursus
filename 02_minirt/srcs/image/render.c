/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 18:04:21 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/16 18:05:53 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_list	*image_node(t_minirt *rt)
{
	t_image	*p_img;
	t_list	*p_node;

	if (!(p_img = image(rt)))
		error_handle(-3, rt);
	if (!(p_node = ft_lstnew((void *)p_img)))
	{
		free(p_img);
		error_handle(-3, rt);
	}
	return (p_node);
}

void			render(t_minirt *rt)
{
	size_t		i;
	size_t		image_size;
	t_list		*p_image;
	t_list		*p_viewport;

	i = 0;
	image_size = ft_lstsize(rt->p_viewport);
	p_viewport = rt->p_viewport;
	while (i < image_size)
	{
		if (!(p_image = image_node(rt)))
			error_handle(-3, rt);
		ft_lstadd_back(&(rt->p_image), p_image);
		printf("\n** image rendering %lu / %zu with %d threads\n",
				i + 1, image_size, NUM_THREAD);
		image_render(rt, p_image->content, p_viewport->content);
		p_image = p_image->next;
		p_viewport = p_viewport->next;
		i++;
	}
	printf("\nRendering complete\n");
}
