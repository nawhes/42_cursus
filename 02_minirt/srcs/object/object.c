/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 05:48:45 by sehpark           #+#    #+#             */
/*   Updated: 2021/01/31 05:16:02 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "object.h"

t_object		*object(void *info, int type, int texture)
{
	t_object	*node;

	if (!(node = malloc(sizeof(t_object))))
		return (NULL);
	node->info = info;
	node->type = type;
	node->texture = texture;
	if (type == OB_SPHERE)
		node->hit = sphere_hit;
	if (type == OB_RECT)
		node->hit = rect_hit;
	return (node);
}
