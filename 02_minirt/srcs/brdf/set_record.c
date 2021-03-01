/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 03:30:30 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 04:52:50 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3		get_albedo(t_object ob)
{
	t_vec3	albedo;

	if (ob.type == OB_SPHERE)
		albedo = ((t_sphere *)ob.info)->rgb;
	if (ob.type == OB_XYRECT)
		albedo = ((t_xyrect *)ob.info)->rgb;
	if (ob.type == OB_XZRECT)
		albedo = ((t_xzrect *)ob.info)->rgb;
	if (ob.type == OB_YZRECT)
		albedo = ((t_yzrect *)ob.info)->rgb;
	

void		set_brdf(t_object ob, t_brdf *brdf)
{
	brdf->attr = ob.attr;
	brdf->texture = ob.texture;
	if (ob.type == OB_SPHERE)
		brdf->albedo = ((t_sphere *)ob.info)->rgb;
	if (ob.type == OB_XYRECT)
		brdf->albedo = ((t_xyrect *)ob.info)->rgb;
	if (ob.type == OB_XZRECT)
		brdf->albedo = ((t_xzrect *)ob.info)->rgb;
	if (ob.type == OB_YZRECT)
		brdf->albedo = ((t_yzrect *)ob.info)->rgb;
	return ;
}
