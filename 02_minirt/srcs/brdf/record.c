/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehpark <sehpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:09:58 by sehpark           #+#    #+#             */
/*   Updated: 2021/03/11 22:19:08 by sehpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_record		record(void)
{
	t_record	this;

	this.t_min = 0.001;
	this.t_max = INFINITY;
	return (this);
}
