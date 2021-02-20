/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 03:30:30 by sehpark           #+#    #+#             */
/*   Updated: 2021/02/20 23:45:20 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		set_record(t_object ob, t_hit_record *rec)
{
	rec->attr = ob.attr;
	rec->texture = ob.texture;
	if (ob.type == OB_SPHERE)
		rec->albedo = ((t_sphere *)ob.info)->rgb;
	if (ob.type == OB_XYRECT)
		rec->albedo = ((t_xyrect *)ob.info)->rgb;
	if (ob.type == OB_XZRECT)
		rec->albedo = ((t_xzrect *)ob.info)->rgb;
	if (ob.type == OB_YZRECT)
		rec->albedo = ((t_yzrect *)ob.info)->rgb;
	return ;
}
