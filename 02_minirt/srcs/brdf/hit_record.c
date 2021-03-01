/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_record.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:09:58 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/02 04:56:45 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_record		hit_record()
{
	t_hit_record	this;

	this.t_min = 0.001;
	this.t_max = INFINITY;
	return (this);
}
